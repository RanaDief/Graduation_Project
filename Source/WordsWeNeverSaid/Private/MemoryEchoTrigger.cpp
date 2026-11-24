
#include "MemoryEchoTrigger.h"

#include "Camera/PlayerCameraManager.h"
#include "Components/PointLightComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MemoryEchoDataAsset.h"
#include "MemoryEchoSubsystem.h"
#include "WWNSLogLibrary.h"

AMemoryEchoTrigger::AMemoryEchoTrigger()
{
    // Ticks only while a visual is animating; see UpdateTickEnabled.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    SetRootComponent(InteractionSphere);

    // Overlap only: the trigger must never block the player or the camera.
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    InteractionSphere->SetGenerateOverlapEvents(true);
    InteractionSphere->SetSphereRadius(InteractionRadius);

    EchoGlow = CreateDefaultSubobject<UPointLightComponent>(TEXT("EchoGlow"));
    EchoGlow->SetupAttachment(InteractionSphere);
    EchoGlow->SetIntensityUnits(ELightUnits::Unitless);
    EchoGlow->SetIntensity(0.0f);
    EchoGlow->SetAttenuationRadius(450.0f);
    EchoGlow->SetCastShadows(false);
    EchoGlow->SetLightColor(GlowColor);

    // Unbound so the look applies wherever the player stands; weight starts at
    // zero, so it costs nothing until an echo plays.
    EchoPostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("EchoPostProcess"));
    EchoPostProcess->SetupAttachment(InteractionSphere);
    EchoPostProcess->bUnbound = true;
    EchoPostProcess->BlendWeight = 0.0f;

    FPostProcessSettings& PP = EchoPostProcess->Settings;
    PP.bOverride_ColorSaturation = true;
    PP.ColorSaturation = FVector4(1.0, 1.0, 1.0, 0.4);      // drained, like an old photograph
    PP.bOverride_ColorGain = true;
    PP.ColorGain = FVector4(1.08, 0.98, 0.82, 1.0);         // warm tint
    PP.bOverride_VignetteIntensity = true;
    PP.VignetteIntensity = 0.9f;
    PP.bOverride_BloomIntensity = true;
    PP.BloomIntensity = 1.4f;
    PP.bOverride_FilmGrainIntensity = true;
    PP.FilmGrainIntensity = 0.35f;
}

void AMemoryEchoTrigger::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Keep the editor preview in step with the properties.
    InteractionSphere->SetSphereRadius(InteractionRadius);
    EchoGlow->SetRelativeLocation(GlowOffset);
    EchoGlow->SetLightColor(GlowColor);
}

void AMemoryEchoTrigger::BeginPlay()
{
    Super::BeginPlay();

    InteractionSphere->SetSphereRadius(InteractionRadius);
    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMemoryEchoTrigger::HandleBeginOverlap);
    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AMemoryEchoTrigger::HandleEndOverlap);

    if (!Memory)
    {
        UWWNSLogLibrary::LogEvent(
            EWWNSLogChannel::Memory, EWWNSLogLevel::Warning,
            TEXT("No Memory asset assigned; this trigger will do nothing."), this);
    }
}

void AMemoryEchoTrigger::HandleBeginOverlap(
    UPrimitiveComponent* /*OverlappedComponent*/, AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/, int32 /*OtherBodyIndex*/, bool /*bFromSweep*/,
    const FHitResult& /*SweepResult*/)
{
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (!Pawn || !Pawn->IsPlayerControlled())
    {
        return;
    }

    APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
    if (!PC)
    {
        return;
    }

    // Route input here while the player stands close enough.
    EnableInput(PC);
    if (InputComponent)
    {
        InputComponent->BindKey(InteractKey, IE_Pressed, this, &AMemoryEchoTrigger::OnInteractPressed);
    }

    bPlayerInRange = true;
    UpdateTickEnabled();

    UWWNSLogLibrary::LogEvent(
        EWWNSLogChannel::Interaction, EWWNSLogLevel::Info,
        FString::Printf(TEXT("In range. Press %s to play the memory."), *InteractKey.ToString()),
        this);
}

void AMemoryEchoTrigger::HandleEndOverlap(
    UPrimitiveComponent* /*OverlappedComponent*/, AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/, int32 /*OtherBodyIndex*/)
{
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (!Pawn || !Pawn->IsPlayerControlled())
    {
        return;
    }

    if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
    {
        DisableInput(PC);
    }

    bPlayerInRange = false;
    UpdateTickEnabled();

    UWWNSLogLibrary::LogEvent(
        EWWNSLogChannel::Interaction, EWWNSLogLevel::Verbose,
        TEXT("Out of range."), this);
}

void AMemoryEchoTrigger::OnInteractPressed()
{
    if (bPlayerInRange)
    {
        PlayMemory();
    }
}

bool AMemoryEchoTrigger::PlayMemory()
{
    if (!Memory)
    {
        UWWNSLogLibrary::LogMemoryEvent(
            NAME_None, TEXT("no Memory asset assigned on this trigger"), false, this);
        return false;
    }

    const UGameInstance* GI = UGameplayStatics::GetGameInstance(this);
    UMemoryEchoSubsystem* Subsystem = GI ? GI->GetSubsystem<UMemoryEchoSubsystem>() : nullptr;
    if (!Subsystem)
    {
        UWWNSLogLibrary::LogMemoryEvent(
            Memory->MemoryID, TEXT("Memory Echo subsystem unavailable"), false, this);
        return false;
    }

    // Bring the presentation up only now, so nothing covers the screen before
    // the player has interacted.
    EnsurePresentation();

    // The subsystem owns the rules: it rejects invalid assets, empty IDs and
    // repeat plays, then broadcasts to the presentation component.
    const bool bActivated = Subsystem->ActivateMemory(Memory);

    UWWNSLogLibrary::LogMemoryEvent(
        Memory->MemoryID,
        bActivated ? TEXT("broadcast to presentation") : TEXT("refused by subsystem, most likely already played"),
        bActivated,
        this);

    if (bActivated)
    {
        bHasPlayed = true;
        BeginEchoVisuals();
    }
    else
    {
        // Nothing to show, so do not leave an empty presentation on screen.
        TearDownPresentation();
    }

    return bActivated;
}

void AMemoryEchoTrigger::BeginEchoVisuals()
{
    if (!bEnableEchoVisuals)
    {
        return;
    }

    bEchoPlaying = true;
    EchoElapsed = 0.0f;

    // A short warm flash marks the moment the memory surfaces.
    if (FlashStrength > 0.0f)
    {
        if (const APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
        {
            if (PC->PlayerCameraManager)
            {
                PC->PlayerCameraManager->StartCameraFade(
                    FlashStrength, 0.0f, EchoFadeSeconds, GlowColor, false, false);
            }
        }
    }

    UpdateTickEnabled();
}

void AMemoryEchoTrigger::EndEchoVisuals()
{
    bEchoPlaying = false;
    UpdateTickEnabled();
}

void AMemoryEchoTrigger::HandlePresentationClosed()
{
    DismissEcho();
}

void AMemoryEchoTrigger::DismissEcho()
{
    TearDownPresentation();
    EndEchoVisuals();
}

void AMemoryEchoTrigger::EnsurePresentation()
{
    if (!PresentationComponentClass || SpawnedPresentation)
    {
        return;
    }

    SpawnedPresentation = NewObject<UActorComponent>(this, PresentationComponentClass);
    if (!SpawnedPresentation)
    {
        return;
    }

    // Registering after BeginPlay runs the component's own BeginPlay, which is
    // where it creates its widget and starts listening to the subsystem.
    SpawnedPresentation->RegisterComponent();

    // The "closed" dispatcher lives on a Blueprint class, so it is found by name.
    if (FMulticastDelegateProperty* Closed = FindFProperty<FMulticastDelegateProperty>(
            SpawnedPresentation->GetClass(), TEXT("OnMemoryPresentationClosed")))
    {
        FScriptDelegate Delegate;
        Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(AMemoryEchoTrigger, HandlePresentationClosed));
        Closed->AddDelegate(MoveTemp(Delegate), SpawnedPresentation);
    }
}

void AMemoryEchoTrigger::TearDownPresentation()
{
    if (!SpawnedPresentation)
    {
        return;
    }

    // Take its widget off screen. Looked up by name to avoid depending on the
    // Blueprint class or on UMG from this module.
    if (const FObjectProperty* WidgetProp = FindFProperty<FObjectProperty>(
            SpawnedPresentation->GetClass(), TEXT("MemoryWidget")))
    {
        if (UObject* Widget = WidgetProp->GetObjectPropertyValue_InContainer(SpawnedPresentation))
        {
            if (UFunction* Remove = Widget->FindFunction(TEXT("RemoveFromParent")))
            {
                Widget->ProcessEvent(Remove, nullptr);
            }
        }
    }

    SpawnedPresentation->DestroyComponent();
    SpawnedPresentation = nullptr;
}

void AMemoryEchoTrigger::UpdateTickEnabled()
{
    // Run while something is animating or still fading back to rest.
    const bool bNeedsTick = bEnableEchoVisuals
        && (bPlayerInRange || bEchoPlaying || EchoAlpha > 0.0f || RangeAlpha > 0.0f);
    SetActorTickEnabled(bNeedsTick);
}

void AMemoryEchoTrigger::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Safety net in case nothing reports that the presentation closed.
    if (bEchoPlaying)
    {
        EchoElapsed += DeltaSeconds;
        if (MaxEchoVisualSeconds > 0.0f && EchoElapsed >= MaxEchoVisualSeconds)
        {
            bEchoPlaying = false;
        }
    }

    const float FadeSpeed = 1.0f / FMath::Max(EchoFadeSeconds, 0.05f);
    EchoAlpha = FMath::FInterpConstantTo(EchoAlpha, bEchoPlaying ? 1.0f : 0.0f, DeltaSeconds, FadeSpeed);

    // Invite interaction only while there is still a memory to play.
    const bool bInvite = bPlayerInRange && !bHasPlayed;
    RangeAlpha = FMath::FInterpConstantTo(RangeAlpha, bInvite ? 1.0f : 0.0f, DeltaSeconds, 2.0f);

    PulseTime += DeltaSeconds;
    const float Pulse = 0.5f + 0.5f * FMath::Sin(PulseTime * PulseRate * 2.0f * UE_PI);
    // Never fully dark while inviting, so the cue stays readable between pulses.
    const float Invite = RangeAlpha * FMath::Lerp(0.35f, 1.0f, Pulse) * GlowIntensity;

    EchoGlow->SetIntensity(FMath::Max(Invite, EchoAlpha * EchoGlowIntensity));
    EchoPostProcess->BlendWeight = FMath::SmoothStep(0.0f, 1.0f, EchoAlpha);

    UpdateTickEnabled();
}


#include "MemoryEchoTrigger.h"

#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MemoryEchoDataAsset.h"
#include "MemoryEchoSubsystem.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "TextureResource.h"
#include "TimerManager.h"
#include "WWNSLogLibrary.h"
#include "Widgets/SLeafWidget.h"

/**
 * Full-screen overlay that draws the darkness mask over the game view.
 * The mask itself is a small texture the trigger repaints while it moves.
 */
class SEchoIris : public SLeafWidget
{
public:
    SLATE_BEGIN_ARGS(SEchoIris) {}
    SLATE_END_ARGS()

    void Construct(const FArguments&)
    {
        SetVisibility(EVisibility::HitTestInvisible);   // never steals input
        SetCanTick(false);
    }

    void SetMask(UTexture2D* Texture, const FIntPoint& Size)
    {
        MaskBrush.SetResourceObject(Texture);
        MaskBrush.ImageSize = FVector2D(Size.X, Size.Y);
        MaskBrush.DrawAs = ESlateBrushDrawType::Image;
    }

    /** 0 = fully open (draws nothing), 1 = fully closed (solid). */
    void SetClosed(float InClosed, const FLinearColor& InColor)
    {
        Closed = FMath::Clamp(InClosed, 0.0f, 1.0f);
        Color = InColor;
    }

    virtual FVector2D ComputeDesiredSize(float) const override { return FVector2D(16.0, 16.0); }

    virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Geo, const FSlateRect& Cull,
        FSlateWindowElementList& Out, int32 Layer, const FWidgetStyle& Style, bool bParentEnabled) const override
    {
        if (Closed <= 0.0f)
        {
            return Layer;
        }

        const FSlateBrush* Brush = (Closed >= 1.0f) ? FCoreStyle::Get().GetBrush("WhiteBrush") : &MaskBrush;
        FSlateDrawElement::MakeBox(Out, Layer, Geo.ToPaintGeometry(), Brush, ESlateDrawEffect::None, Color);
        return Layer;
    }

private:
    FSlateBrush MaskBrush;
    FLinearColor Color = FLinearColor::Black;
    float Closed = 0.0f;
};

namespace
{
    // Small on purpose: it is stretched over the screen and the softness hides it.
    const FIntPoint IrisMaskSize(192, 108);
}

AMemoryEchoTrigger::AMemoryEchoTrigger()
{
    // Ticks only while the iris is animating; see UpdateTickEnabled.
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
}

void AMemoryEchoTrigger::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Keep the editor preview in step with the properties.
    InteractionSphere->SetSphereRadius(InteractionRadius);
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
        Interact();
    }
}

void AMemoryEchoTrigger::Interact()
{
    if (bPlayPending || bEchoPlaying)
    {
        return;
    }

    // No lead-in when there is nothing to lead into, or when it is switched off.
    if (!bEnableEchoVisuals || PresentationDelaySeconds <= 0.0f || bHasPlayed || !Memory)
    {
        PlayMemory();
        return;
    }

    bPlayPending = true;
    BeginEchoVisuals();
    GetWorldTimerManager().SetTimer(
        PendingPlayTimer, this, &AMemoryEchoTrigger::FinishPendingPlay, PresentationDelaySeconds, false);
}

void AMemoryEchoTrigger::FinishPendingPlay()
{
    bPlayPending = false;

    // If the subsystem refuses after all, do not leave the look hanging.
    if (!PlayMemory())
    {
        EndEchoVisuals();
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
        if (!bEchoPlaying)
        {
            BeginEchoVisuals();
        }
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

    EnsureIris();
    bEchoPlaying = true;
    EchoElapsed = 0.0f;
    UpdateTickEnabled();
}

void AMemoryEchoTrigger::EndEchoVisuals()
{
    bEchoPlaying = false;
    UpdateTickEnabled();
}

void AMemoryEchoTrigger::EnsureIris()
{
    if (IrisWidget.IsValid())
    {
        return;
    }

    UGameViewportClient* Viewport = GetWorld() ? GetWorld()->GetGameViewport() : nullptr;
    if (!Viewport)
    {
        return;
    }

    if (!IrisTexture)
    {
        IrisTexture = UTexture2D::CreateTransient(IrisMaskSize.X, IrisMaskSize.Y, PF_B8G8R8A8);
        IrisTexture->SRGB = false;
        IrisTexture->AddressX = TA_Clamp;
        IrisTexture->AddressY = TA_Clamp;

        // Start fully clear.
        FTexture2DMipMap& Mip = IrisTexture->GetPlatformData()->Mips[0];
        FMemory::Memzero(Mip.BulkData.Lock(LOCK_READ_WRITE), IrisMaskSize.X * IrisMaskSize.Y * sizeof(FColor));
        Mip.BulkData.Unlock();
        IrisTexture->UpdateResource();
    }

    IrisWidget = SNew(SEchoIris);
    IrisWidget->SetMask(IrisTexture, IrisMaskSize);
    // Below the game's own UI, so the memory screen is drawn on top of it.
    Viewport->AddViewportWidgetContent(IrisWidget.ToSharedRef(), -100);
}

void AMemoryEchoTrigger::RedrawIris()
{
    if (!IrisTexture || !GetWorld())
    {
        return;
    }

    const int32 W = IrisMaskSize.X;
    const int32 H = IrisMaskSize.Y;

    FVector2D ViewSize(16.0, 9.0);
    if (const UGameViewportClient* Viewport = GetWorld()->GetGameViewport())
    {
        Viewport->GetViewportSize(ViewSize);
    }
    const float Aspect = ViewSize.Y > 1.0 ? static_cast<float>(ViewSize.X / ViewSize.Y) : 1.777f;
    const float CornerLength = FMath::Sqrt(Aspect * Aspect + 1.0f);
    const float Time = GetWorld()->GetTimeSeconds();

    // The edge creeps at a steady pace, then takes the centre faster at the end.
    const float C = IrisClosed;
    const float Progress = 0.65f * C + 0.35f * C * C * C;
    const float Amp = 0.55f * EdgeRoughness;
    const float Edge = FMath::Lerp(1.0f + 0.35f * Amp, -(0.8f * Amp + EdgeSoftness), Progress);
    // Ease the mask in at the very start and force it shut at the very end, so
    // nothing pops when it appears and no pinprick of light is left behind.
    const float FadeIn = FMath::SmoothStep(0.0f, 0.08f, C);
    const float ForceShut = FMath::SmoothStep(0.88f, 1.0f, C);
    const float Drift = Time * 0.11f;

    uint8* Data = static_cast<uint8*>(FMemory::Malloc(W * H * 4));
    for (int32 Y = 0; Y < H; ++Y)
    {
        const float Py = (Y + 0.5f) / H * 2.0f - 1.0f;
        for (int32 X = 0; X < W; ++X)
        {
            const float Px = ((X + 0.5f) / W * 2.0f - 1.0f) * Aspect;
            const float R = FMath::Sqrt(Px * Px + Py * Py) / CornerLength;   // 0 centre, 1 corner

            // Warp the sample position with slow noise first. This bends the
            // shapes into curls, like smoke or ink in water, instead of rays.
            const float WarpX = FMath::PerlinNoise3D(FVector(Px * 0.9 + 5.2, Py * 0.9 + 1.3, Drift));
            const float WarpY = FMath::PerlinNoise3D(FVector(Px * 0.9 - 8.7, Py * 0.9 + 6.1, Drift + 3.7));
            const float Qx = Px + 0.75f * WarpX;
            const float Qy = Py + 0.75f * WarpY;

            // Layered noise on the warped position: broad billows, then detail.
            const float Billow = FMath::PerlinNoise3D(FVector(Qx * 1.15 + 11.3, Qy * 1.15 - 4.1, Drift * 1.3));
            const float Curl = FMath::PerlinNoise3D(FVector(Qx * 2.6 - 7.7, Qy * 2.6 + 2.9, Drift * 2.1));
            const float Wisp = FMath::PerlinNoise3D(FVector(Qx * 5.4 + 3.1, Qy * 5.4 - 9.4, Drift * 3.4));
            const float Noise = 0.60f * Billow + 0.28f * Curl + 0.12f * Wisp;

            // Some stretches of the edge are wispy and some are dense.
            const float SoftVary = 0.5f + 0.5f * FMath::PerlinNoise3D(FVector(Px * 0.7 - 2.0, Py * 0.7 + 14.0, Drift * 0.8));
            const float Soft = EdgeSoftness * FMath::Lerp(0.55f, 1.7f, SoftVary);

            const float Value = R + Amp * 2.0f * Noise;
            float Alpha = FMath::SmoothStep(Edge - Soft, Edge + Soft, Value) * FadeIn;
            Alpha = FMath::Max(Alpha, ForceShut);

            uint8* P = Data + (Y * W + X) * 4;
            P[0] = 255; P[1] = 255; P[2] = 255;
            P[3] = static_cast<uint8>(FMath::RoundToInt(FMath::Clamp(Alpha, 0.0f, 1.0f) * 255.0f));
        }
    }

    FUpdateTextureRegion2D* Region = new FUpdateTextureRegion2D(0, 0, 0, 0, W, H);
    IrisTexture->UpdateTextureRegions(0, 1, Region, W * 4, 4, Data,
        [](uint8* InData, const FUpdateTextureRegion2D* InRegion)
        {
            FMemory::Free(InData);
            delete InRegion;
        });
}

void AMemoryEchoTrigger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (IrisWidget.IsValid())
    {
        if (UGameViewportClient* Viewport = GetWorld() ? GetWorld()->GetGameViewport() : nullptr)
        {
            Viewport->RemoveViewportWidgetContent(IrisWidget.ToSharedRef());
        }
        IrisWidget.Reset();
    }

    Super::EndPlay(EndPlayReason);
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
    // Run only while the iris is moving, or closed with a time limit to watch.
    const float Target = bEchoPlaying ? 1.0f : 0.0f;
    const bool bNeedsTick = bEnableEchoVisuals
        && (!FMath::IsNearlyEqual(IrisClosed, Target) || (bEchoPlaying && MaxEchoVisualSeconds > 0.0f));
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
            EndEchoVisuals();
        }
    }

    // Close over the lead-in so the view is shut just as the memory screen
    // appears; open again at the fade-out speed.
    const float CloseSpeed = 1.0f / FMath::Max(PresentationDelaySeconds, 0.15f);
    const float OpenSpeed = 1.0f / FMath::Max(EchoFadeSeconds, 0.05f);
    IrisClosed = FMath::FInterpConstantTo(
        IrisClosed, bEchoPlaying ? 1.0f : 0.0f, DeltaSeconds, bEchoPlaying ? CloseSpeed : OpenSpeed);

    if (IrisWidget.IsValid())
    {
        if (IrisClosed > 0.0f && IrisClosed < 1.0f)
        {
            RedrawIris();
        }
        IrisWidget->SetClosed(IrisClosed, EchoFadeColor);
    }

    UpdateTickEnabled();
}

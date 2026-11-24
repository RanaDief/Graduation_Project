
#include "MemoryEchoTrigger.h"

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
    PrimaryActorTick.bCanEverTick = false;

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    SetRootComponent(InteractionSphere);

    // Overlap only: the trigger must never block the player or the camera.
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    InteractionSphere->SetGenerateOverlapEvents(true);
    InteractionSphere->SetSphereRadius(InteractionRadius);
}

void AMemoryEchoTrigger::BeginPlay()
{
    Super::BeginPlay();

    InteractionSphere->SetSphereRadius(InteractionRadius);
    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMemoryEchoTrigger::HandleBeginOverlap);
    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AMemoryEchoTrigger::HandleEndOverlap);

    // Optionally bring the presentation component with us, so dropping this one
    // actor into a level is enough to see an echo.
    if (PresentationComponentClass)
    {
        if (UActorComponent* Presentation =
                NewObject<UActorComponent>(this, PresentationComponentClass, TEXT("MemoryEchoPresentation")))
        {
            Presentation->RegisterComponent();
        }
    }

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

    // The subsystem owns the rules: it rejects invalid assets, empty IDs and
    // repeat plays, then broadcasts to the presentation component.
    const bool bActivated = Subsystem->ActivateMemory(Memory);

    UWWNSLogLibrary::LogMemoryEvent(
        Memory->MemoryID,
        bActivated ? TEXT("broadcast to presentation") : TEXT("refused by subsystem, most likely already played"),
        bActivated,
        this);

    return bActivated;
}

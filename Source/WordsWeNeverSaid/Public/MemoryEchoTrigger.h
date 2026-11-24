
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputCoreTypes.h"
#include "MemoryEchoTrigger.generated.h"

class USphereComponent;
class UMemoryEchoDataAsset;

/**
 * Place this on an object that should play a Memory Echo when the player
 * interacts with it, for example the family photograph in Level 1.
 *
 * Matches the trigger flow in Docs/Gameplay/Memory-Echoes.md:
 *     Interact -> Echo Plays -> Visual Appears -> Echo Ends
 *
 * It only asks the Memory Echo subsystem to activate a memory. Presentation
 * stays with BP_MemoryEchoPresentationComponent, which already listens for
 * OnMemoryActivated, so this adds no second copy of that logic.
 *
 * The proximity-and-keypress interaction here is deliberately temporary: it
 * exists so echoes can be demonstrated before the player character and the
 * interaction component land. Once those exist, call PlayMemory from the real
 * interaction path and drop the input handling.
 */
UCLASS()
class WORDSWENEVERSAID_API AMemoryEchoTrigger : public AActor
{
    GENERATED_BODY()

public:

    AMemoryEchoTrigger();

    /** The memory to activate. Leave empty and the trigger does nothing. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
    TObjectPtr<UMemoryEchoDataAsset> Memory;

    /** How close the player must be before the trigger listens for the key. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo",
        meta = (ClampMin = "25.0", UIMin = "25.0"))
    float InteractionRadius = 200.0f;

    /** Temporary interaction key, replaced once Enhanced Input mappings exist. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
    FKey InteractKey = EKeys::E;

    /**
     * Optional. Set this to BP_MemoryEchoPresentationComponent and the trigger
     * spawns one at BeginPlay, so a level needs nothing else wired up to show
     * the echo. Leave it empty when the player or game mode already owns one.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
    TSubclassOf<UActorComponent> PresentationComponentClass;

    /**
     * Activate the memory. Safe to call from Blueprint or from the real
     * interaction system later.
     * @return true if the subsystem accepted it; false if it was invalid or
     *         had already played.
     */
    UFUNCTION(BlueprintCallable, Category = "Memory Echo")
    bool PlayMemory();

protected:

    virtual void BeginPlay() override;

    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

    void OnInteractPressed();

    /** Range in which the player may interact. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Memory Echo",
        meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> InteractionSphere;

    /** Whether input is currently routed here. */
    bool bPlayerInRange = false;
};

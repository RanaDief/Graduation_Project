
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputCoreTypes.h"
#include "MemoryEchoTrigger.generated.h"

class USphereComponent;
class UTexture2D;
class SEchoIris;
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
     * creates one at the moment the echo plays and removes it when the player
     * closes it, so a level needs nothing else wired up and the screen stays
     * clear until then. Leave it empty when the player or game mode owns one.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo")
    TSubclassOf<UActorComponent> PresentationComponentClass;

    // ---- Echo visuals -------------------------------------------------------
    // Nothing happens to the room until the player interacts. On interaction
    // darkness creeps in from the edges of the screen toward the centre in
    // uneven, drifting fingers, slowly at first and then swallowing the middle.
    // It draws back the same way when the echo is dismissed.

    /** Turn the iris transition on or off for this trigger. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals")
    bool bEnableEchoVisuals = true;

    /** Colour the view closes to. Black leads straight into the memory screen. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals")
    FLinearColor EchoFadeColor = FLinearColor::Black;

    /** How ragged the advancing edge is. 0 is a clean circle, 1 is very torn. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float EdgeRoughness = 0.75f;

    /** Width of the soft falloff at the edge of the darkness. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.02", ClampMax = "0.6"))
    float EdgeSoftness = 0.16f;

    /** Seconds for the view to open back up after the echo is dismissed. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.05"))
    float EchoFadeSeconds = 3.0f;

    /**
     * Safety limit, in seconds, on how long the view stays closed. It normally
     * opens when the presentation closes; this covers the case where nothing
     * reports that. 0 means no limit.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0"))
    float MaxEchoVisualSeconds = 30.0f;

    /** Open the view early, e.g. from a custom presentation. */
    UFUNCTION(BlueprintCallable, Category = "Memory Echo|Visuals")
    void EndEchoVisuals();

    /**
     * Seconds the view takes to close in, and so the gap between interacting
     * and the memory screen appearing. 0 shows the screen at once.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0"))
    float PresentationDelaySeconds = 4.5f;

    /**
     * What the interact key does: starts the echo visuals, then plays the
     * memory after PresentationDelaySeconds. Call this from the real
     * interaction system; use PlayMemory to skip the lead-in.
     */
    UFUNCTION(BlueprintCallable, Category = "Memory Echo")
    void Interact();

    /** Close the echo: removes the presentation this trigger created and ends the look. */
    UFUNCTION(BlueprintCallable, Category = "Memory Echo")
    void DismissEcho();

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
    virtual void Tick(float DeltaSeconds) override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

    void OnInteractPressed();

    void BeginEchoVisuals();
    void EnsureIris();
    void RedrawIris();
    void FinishPendingPlay();
    void EnsurePresentation();
    void TearDownPresentation();
    void UpdateTickEnabled();

    /** Bound to the presentation component's OnMemoryPresentationClosed, when it has one. */
    UFUNCTION()
    void HandlePresentationClosed();

    /** The darkness mask, redrawn each frame while it moves; no asset needed. */
    UPROPERTY(Transient)
    TObjectPtr<UTexture2D> IrisTexture;

    /** The full-screen widget that draws the mask. */
    TSharedPtr<SEchoIris> IrisWidget;

    /** Presentation component created by this trigger, if any. */
    UPROPERTY(Transient)
    TObjectPtr<UActorComponent> SpawnedPresentation;

    FTimerHandle PendingPlayTimer;
    bool bPlayPending = false;   // visuals started, memory screen not shown yet
    bool bEchoPlaying = false;   // view is closed or closing
    bool bHasPlayed = false;     // the memory is spent
    float IrisClosed = 0.0f;     // 0 = view fully open, 1 = fully closed
    float EchoElapsed = 0.0f;

    /** Range in which the player may interact. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Memory Echo",
        meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> InteractionSphere;

    /** Whether input is currently routed here. */
    bool bPlayerInRange = false;
};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputCoreTypes.h"
#include "MemoryEchoTrigger.generated.h"

class USphereComponent;
class UPointLightComponent;
class UPostProcessComponent;
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
    // A readable cue that the object matters, then a short "remembered" look
    // while the echo plays. Kept gentle on purpose: no shake, no hard cuts.

    /** Turn the glow, flash and memory look on or off for this trigger. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals")
    bool bEnableEchoVisuals = true;

    /** Colour of the glow and of the flash when the echo starts. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals")
    FLinearColor GlowColor = FLinearColor(1.0f, 0.78f, 0.52f);

    /** Peak brightness of the slow pulse shown while the player is in range. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0"))
    float GlowIntensity = 1200.0f;

    /** Brightness of the glow while the echo is playing. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0"))
    float EchoGlowIntensity = 2600.0f;

    /** Pulses per second while waiting for the player to interact. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.05"))
    float PulseRate = 0.6f;

    /** Where the glow sits relative to the trigger, e.g. raised onto a wall photo. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals")
    FVector GlowOffset = FVector::ZeroVector;

    /** Seconds for the memory look to fade in and out. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.05"))
    float EchoFadeSeconds = 1.2f;

    /** Strength of the brief flash when the echo starts. 0 disables it. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float FlashStrength = 0.45f;

    /**
     * Safety limit for the memory look, in seconds. It normally ends when the
     * presentation closes; this covers the case where nothing reports that.
     * 0 means no limit.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Memory Echo|Visuals", meta = (ClampMin = "0.0"))
    float MaxEchoVisualSeconds = 30.0f;

    /** Close the echo: removes the presentation this trigger created and ends the look. */
    UFUNCTION(BlueprintCallable, Category = "Memory Echo")
    void DismissEcho();

    /** End the memory look early, e.g. from a custom presentation. */
    UFUNCTION(BlueprintCallable, Category = "Memory Echo|Visuals")
    void EndEchoVisuals();

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
    void EnsurePresentation();
    void TearDownPresentation();
    void UpdateTickEnabled();

    /** Bound to the presentation component's OnMemoryPresentationClosed, when it has one. */
    UFUNCTION()
    void HandlePresentationClosed();

    /** Warm light that marks the object and swells while the echo plays. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Memory Echo|Visuals",
        meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UPointLightComponent> EchoGlow;

    /** Faded, warm-tinted look blended in for the length of the echo. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Memory Echo|Visuals",
        meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UPostProcessComponent> EchoPostProcess;

    /** Presentation component created by this trigger, if any. */
    UPROPERTY(Transient)
    TObjectPtr<UActorComponent> SpawnedPresentation;

    bool bEchoPlaying = false;   // memory look is on
    bool bHasPlayed = false;     // stop inviting interaction once the memory is spent
    float EchoAlpha = 0.0f;      // 0..1 blend of the memory look
    float RangeAlpha = 0.0f;     // 0..1 blend of the in-range pulse
    float PulseTime = 0.0f;
    float EchoElapsed = 0.0f;

    /** Range in which the player may interact. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Memory Echo",
        meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> InteractionSphere;

    /** Whether input is currently routed here. */
    bool bPlayerInRange = false;
};

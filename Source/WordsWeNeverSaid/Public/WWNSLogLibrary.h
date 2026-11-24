
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WWNSLogLibrary.generated.h"

/** Which system a log line belongs to. Mirrors the categories in WWNSLog.h. */
UENUM(BlueprintType)
enum class EWWNSLogChannel : uint8
{
    Progression UMETA(DisplayName = "Progression"),
    Puzzle      UMETA(DisplayName = "Puzzle"),
    Memory      UMETA(DisplayName = "Memory Echo"),
    Interaction UMETA(DisplayName = "Interaction"),
    Save        UMETA(DisplayName = "Save")
};

/** Severity of a log line. Warning and Error are the ones to watch in a playtest log. */
UENUM(BlueprintType)
enum class EWWNSLogLevel : uint8
{
    Verbose UMETA(DisplayName = "Verbose"),
    Info    UMETA(DisplayName = "Info"),
    Warning UMETA(DisplayName = "Warning"),
    Error   UMETA(DisplayName = "Error")
};

/**
 * Logging entry points for both C++ and Blueprint.
 *
 * Prefer these over Print String: Print String is editor-only and is lost in a
 * packaged playtest, which is exactly where progression blockers show up.
 */
UCLASS()
class WORDSWENEVERSAID_API UWWNSLogLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    /** Log a message to one of the project's categories. */
    UFUNCTION(BlueprintCallable, Category = "WWNS|Logging",
        meta = (DefaultToSelf = "Context", AdvancedDisplay = "Context"))
    static void LogEvent(
        EWWNSLogChannel Channel,
        EWWNSLogLevel Level,
        const FString& Message,
        const UObject* Context = nullptr);

    /** Record why a puzzle attempt was rejected, so a stuck playtester can be explained afterwards. */
    UFUNCTION(BlueprintCallable, Category = "WWNS|Logging",
        meta = (DefaultToSelf = "Context", AdvancedDisplay = "Context"))
    static void LogPuzzleFailure(
        FName PuzzleID,
        const FString& Reason,
        const UObject* Context = nullptr);

    /** Record a story flag or level change as it happens. */
    UFUNCTION(BlueprintCallable, Category = "WWNS|Logging",
        meta = (DefaultToSelf = "Context", AdvancedDisplay = "Context"))
    static void LogProgression(
        FName StoryFlag,
        const FString& Detail,
        const UObject* Context = nullptr);

    /** Record that a memory echo was activated, or refused and why. */
    UFUNCTION(BlueprintCallable, Category = "WWNS|Logging",
        meta = (DefaultToSelf = "Context", AdvancedDisplay = "Context"))
    static void LogMemoryEvent(
        FName MemoryID,
        const FString& Detail,
        bool bSucceeded,
        const UObject* Context = nullptr);
};

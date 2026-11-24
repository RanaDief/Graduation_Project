
#include "WWNSLogLibrary.h"
#include "WWNSLog.h"

namespace
{
    // The log macros need a compile-time category, so a runtime channel is
    // resolved to its category object here and logged through FMsg::Logf.
    const FLogCategoryBase& ResolveCategory(EWWNSLogChannel Channel)
    {
        switch (Channel)
        {
        case EWWNSLogChannel::Puzzle:      return LogWWNSPuzzle;
        case EWWNSLogChannel::Memory:      return LogWWNSMemory;
        case EWWNSLogChannel::Interaction: return LogWWNSInteraction;
        case EWWNSLogChannel::Save:        return LogWWNSSave;
        case EWWNSLogChannel::Progression:
        default:                           return LogWWNSProgression;
        }
    }

    ELogVerbosity::Type ResolveVerbosity(EWWNSLogLevel Level)
    {
        switch (Level)
        {
        case EWWNSLogLevel::Verbose: return ELogVerbosity::Verbose;
        case EWWNSLogLevel::Warning: return ELogVerbosity::Warning;
        case EWWNSLogLevel::Error:   return ELogVerbosity::Error;
        case EWWNSLogLevel::Info:
        default:                     return ELogVerbosity::Log;
        }
    }
}

void UWWNSLogLibrary::LogEvent(
    EWWNSLogChannel Channel,
    EWWNSLogLevel Level,
    const FString& Message,
    const UObject* Context)
{
#if !NO_LOGGING
    const FLogCategoryBase& Category = ResolveCategory(Channel);
    const ELogVerbosity::Type Verbosity = ResolveVerbosity(Level);

    // Respect the category's configured verbosity so a noisy channel can be quietened
    // at runtime with the console, e.g. "Log LogWWNSPuzzle Warning".
    if (Category.IsSuppressed(Verbosity))
    {
        return;
    }

    // Naming the acting object makes a log usable when several actors share a class.
    const FString Line = IsValid(Context)
        ? FString::Printf(TEXT("[%s] %s"), *Context->GetName(), *Message)
        : Message;

    FMsg::Logf(__FILE__, __LINE__, Category.GetCategoryName(), Verbosity, TEXT("%s"), *Line);
#endif
}

void UWWNSLogLibrary::LogPuzzleFailure(
    FName PuzzleID,
    const FString& Reason,
    const UObject* Context)
{
    // Warning rather than Error: a rejected attempt is expected play, not a fault.
    LogEvent(
        EWWNSLogChannel::Puzzle,
        EWWNSLogLevel::Warning,
        FString::Printf(TEXT("Puzzle '%s' rejected an attempt: %s"), *PuzzleID.ToString(), *Reason),
        Context);
}

void UWWNSLogLibrary::LogProgression(
    FName StoryFlag,
    const FString& Detail,
    const UObject* Context)
{
    LogEvent(
        EWWNSLogChannel::Progression,
        EWWNSLogLevel::Info,
        FString::Printf(TEXT("Progression '%s': %s"), *StoryFlag.ToString(), *Detail),
        Context);
}

void UWWNSLogLibrary::LogMemoryEvent(
    FName MemoryID,
    const FString& Detail,
    bool bSucceeded,
    const UObject* Context)
{
    LogEvent(
        EWWNSLogChannel::Memory,
        bSucceeded ? EWWNSLogLevel::Info : EWWNSLogLevel::Warning,
        FString::Printf(
            TEXT("Memory '%s' %s: %s"),
            *MemoryID.ToString(),
            bSucceeded ? TEXT("activated") : TEXT("not activated"),
            *Detail),
        Context);
}

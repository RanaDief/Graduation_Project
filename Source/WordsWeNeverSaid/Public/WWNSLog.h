
#pragma once

#include "CoreMinimal.h"

// Shared log categories for Words We Never Said.
//
// One category per system so a playtest log can be filtered down to the
// subsystem being diagnosed, e.g. in the editor console:
//
//     Log LogWWNSPuzzle Verbose
//     Log LogWWNSProgression Verbose
//
// Blueprint graphs should log through UWWNSLogLibrary rather than Print String,
// so that playtest output survives outside a PIE session.

WORDSWENEVERSAID_API DECLARE_LOG_CATEGORY_EXTERN(LogWWNSProgression, Log, All);
WORDSWENEVERSAID_API DECLARE_LOG_CATEGORY_EXTERN(LogWWNSPuzzle, Log, All);
WORDSWENEVERSAID_API DECLARE_LOG_CATEGORY_EXTERN(LogWWNSMemory, Log, All);
WORDSWENEVERSAID_API DECLARE_LOG_CATEGORY_EXTERN(LogWWNSInteraction, Log, All);
WORDSWENEVERSAID_API DECLARE_LOG_CATEGORY_EXTERN(LogWWNSSave, Log, All);

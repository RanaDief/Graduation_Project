
#pragma once

#include "CoreMinimal.h"
#include "Engine/PrimaryDataAsset.h"
#include "MemoryEchoDataAsset.generated.h"

UCLASS(BlueprintType)
class WORDSWENEVERSAID_API UMemoryEchoDataAsset
    : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    // Unique identifier for this memory
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Memory")
    FName MemoryID;

    // Name displayed to the player or used by the UI
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Memory")
    FText MemoryTitle;

    // Description of the memory
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Memory")
    FText MemoryDescription;

    // Text or narrative associated with this memory
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Memory")
    FText MemoryContent;

    // IDs of clues required to unlock this memory
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Memory")
    TArray<FName> RequiredClueIDs;
};

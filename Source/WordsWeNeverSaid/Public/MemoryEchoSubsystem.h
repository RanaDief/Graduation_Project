
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MemoryEchoSubsystem.generated.h"

class UMemoryEchoDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnMemoryActivated,
    UMemoryEchoDataAsset*,
    ActivatedMemory
);

UCLASS()
class WORDSWENEVERSAID_API UMemoryEchoSubsystem
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintAssignable, Category = "Memory Echo")
    FOnMemoryActivated OnMemoryActivated;

    UFUNCTION(BlueprintCallable, Category = "Memory Echo")
    bool ActivateMemory(UMemoryEchoDataAsset* Memory);

private:

    TSet<FName> ActivatedMemoryIDs;
};


#include "MemoryEchoSubsystem.h"
#include "MemoryEchoDataAsset.h"

bool UMemoryEchoSubsystem::ActivateMemory(UMemoryEchoDataAsset* Memory)
{
    // 1. Validate the memory asset
    if (!IsValid(Memory))
    {
        return false;
    }

    // 2. Validate its unique ID
    if (Memory->MemoryID.IsNone())
    {
        return false;
    }

    // 3. Prevent duplicate activation
    if (ActivatedMemoryIDs.Contains(Memory->MemoryID))
    {
        return false;
    }

    // 4. Register the activated memory
    ActivatedMemoryIDs.Add(Memory->MemoryID);

    // 5. Notify all listeners
    OnMemoryActivated.Broadcast(Memory);

    return true;
}

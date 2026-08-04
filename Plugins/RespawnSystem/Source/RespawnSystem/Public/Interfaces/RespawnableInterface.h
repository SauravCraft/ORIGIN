#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RespawnableInterface.generated.h"

UINTERFACE(BlueprintType)
class RESPAWNSYSTEM_API URespawnableInterface : public UInterface
{
    GENERATED_BODY()
};

class RESPAWNSYSTEM_API IRespawnableInterface
{
    GENERATED_BODY()

public:

    /** Can this actor activate a checkpoint? */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    bool CanActivateCheckpoint() const;

};
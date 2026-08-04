#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OriginSaveGame.generated.h"

UCLASS()
class ORIGIN_API UOriginSaveGame : public USaveGame
{
    GENERATED_BODY()

public:

    UOriginSaveGame();

    /** Player */
    UPROPERTY(BlueprintReadWrite)
    FVector PlayerLocation;

    UPROPERTY(BlueprintReadWrite)
    FRotator PlayerRotation;

    UPROPERTY(BlueprintReadWrite)
    float Health = 100.f;

    /** Current Respawn Checkpoint */
    UPROPERTY(BlueprintReadWrite)
    FName CurrentCheckpoint;

    UPROPERTY(BlueprintReadWrite)
    FTransform CurrentCheckpointTransform;

    /** Activated Checkpoints */
    UPROPERTY(BlueprintReadWrite)
    TArray<FName> ActiveCheckpoints;

    /** Save Slot */
    UPROPERTY(BlueprintReadWrite)
    FString SlotName;

    UPROPERTY(BlueprintReadWrite)
    int32 UserIndex;
};
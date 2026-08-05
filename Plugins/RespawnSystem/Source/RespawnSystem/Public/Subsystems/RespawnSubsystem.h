#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RespawnSubsystem.generated.h"

class APawn;
class USaveGameData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCheckpointActivated, FTransform);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerRespawned, APawn*);

UCLASS()
class RESPAWNSYSTEM_API URespawnSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Set active checkpoint */
    void SetCheckpoint(FTransform Checkpoint);

    /** Respawn an existing pawn */
    bool RespawnPlayer(APawn* Player);

    /** Current checkpoint */
    FORCEINLINE FTransform GetCurrentCheckpoint() const
    {
        return CurrentCheckpoint;
    }


    // Save System 

    UFUNCTION()
    void HandleSave(USaveGameData* SaveGame);

    UFUNCTION()
    void HandleLoad(USaveGameData* SaveGame);


    //  Delegates 

    FOnCheckpointActivated OnCheckpointActivated;
    FOnPlayerRespawned OnPlayerRespawned;

private:

    UPROPERTY()
    FTransform CurrentCheckpoint;

};
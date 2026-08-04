#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerSubsystem.generated.h"

class USaveGameData;

UCLASS()
class SAVESYSTEM_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Save / Load
    void SaveGame();
    void LoadGame();

    // Checkpoint
    void SetCurrentCheckpoint(const FName& CheckpointID,
        const FTransform& Transform);

//    // Access SaveObject
//    FORCEINLINE USaveGameData* GetSaveObject() const
//    {
//        return SaveObject;
//    }
//
//    const FTransform& GetCheckpointTransform() const;
//
//
//private:
//
//    //UPROPERTY()
//    //USaveGameData* SaveObject;
//
//    FString SlotName = TEXT("PlayerSave");
//
//    int32 UserIndex = 0;
//
//private:
//
//    AOriginCharacter* GetPlayerCharacter() const;

};
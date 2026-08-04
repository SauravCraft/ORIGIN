#include "Subsystems/SaveManagerSubsystem.h"

#include "SaveGames/SaveGameData.h"

#include "Kismet/GameplayStatics.h"

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UE_LOG(LogTemp, Log, TEXT("SaveManager Initialized"));
}

void USaveManagerSubsystem::Deinitialize()
{
    Super::Deinitialize();

    UE_LOG(LogTemp, Log, TEXT("SaveManager Deinitialized"));
}


bool USaveManagerSubsystem::SaveGame()
{

    UE_LOG(LogTemp, Error, TEXT("===== SaveGame() CALLED ====="));

    if (!CurrentSaveGame)
    {
        CurrentSaveGame =
            Cast<USaveGameData>(
                UGameplayStatics::CreateSaveGameObject(
                    USaveGameData::StaticClass()));

        if (!CurrentSaveGame)
        {
            return false;
        }
    }

    // Ask every plugin to write its data first
    OnGameSaved.Broadcast(CurrentSaveGame);

    // Then save to disk
    if (!UGameplayStatics::SaveGameToSlot(
        CurrentSaveGame,
        SaveSlot,
        UserIndex))
    {
        return false;
    }

    UE_LOG(LogTemp, Warning, TEXT("Game Saved"));

    return true;
}


bool USaveManagerSubsystem::LoadGame()
{
    if (!UGameplayStatics::DoesSaveGameExist(
        SaveSlot,
        UserIndex))
    {
        return false;
    }

    CurrentSaveGame =
        Cast<USaveGameData>(
            UGameplayStatics::LoadGameFromSlot(
                SaveSlot,
                UserIndex));

    if (!CurrentSaveGame)
    {
        return false;
    }

    // Restore data here

    OnGameLoaded.Broadcast(CurrentSaveGame);

    UE_LOG(LogTemp, Warning, TEXT("Game Loaded"));

    return true;
}


void USaveManagerSubsystem::SetSaveSlot(const FString& NewSlot)
{
    SaveSlot = NewSlot;
}

FString USaveManagerSubsystem::GetSaveSlot() const
{
    return SaveSlot;
}


//void USaveManagerSubsystem::SaveCheckpoint(const FTransform& CheckpointTransform)
//{
//    if (!CurrentSaveGame)
//    {
//        CurrentSaveGame = Cast<USaveGameData>(
//            UGameplayStatics::CreateSaveGameObject(
//                USaveGameData::StaticClass()));
//
//        if (!CurrentSaveGame)
//        {
//            return;
//        }
//    }
//
//    CurrentSaveGame->CurrentCheckpointTransform = CheckpointTransform;
//
//    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Saved"));
//}
//
//
//FTransform USaveManagerSubsystem::GetCheckpointTransform() const
//{
//    if (!CurrentSaveGame)
//    {
//        return FTransform::Identity;
//    }
//
//    return CurrentSaveGame->CurrentCheckpointTransform;
//}
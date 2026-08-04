#include "Subsystems/SaveManagerSubsystem.h"
#include "SaveGames/SaveGameData.h"
#include "Kismet/GameplayStatics.h"

void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    //if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    //{
    //    SaveObject = Cast<USaveGameData>(
    //        UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    //}
    //else
    //{
    //    SaveObject = Cast<UOriginSaveGame>(
    //        UGameplayStatics::CreateSaveGameObject(
    //            UOriginSaveGame::StaticClass()));
    //}
}

void USaveManagerSubsystem::SaveGame()
{

    //AOriginCharacter* Player = GetPlayerCharacter();

    //if (!Player || !SaveObject)
    //{
    //    return;
    //}

    //SaveObject->PlayerLocation = Player->GetActorLocation();
    //SaveObject->PlayerRotation = Player->GetActorRotation();

    //UGameplayStatics::SaveGameToSlot(
    //    SaveObject,
    //    SlotName,
    //    UserIndex);
}

void USaveManagerSubsystem::LoadGame()
{
    //AOriginCharacter* Player = GetPlayerCharacter();

    //if (!Player || !SaveObject)
    //{
    //    return;
    //}

    //if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    //{
    //    return;
    //}

    ////SaveObject = Cast<UOriginSaveGame>(
    ////    UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

    //Player->SetActorLocation(SaveObject->PlayerLocation);
    //Player->SetActorRotation(SaveObject->PlayerRotation);
}

void USaveManagerSubsystem::SetCurrentCheckpoint(
    const FName& CheckpointID,
    const FTransform& Transform)
{
    //if (!SaveObject)
    //{
    //    return;
    //}

    //SaveObject->CurrentCheckpoint = CheckpointID;
    //SaveObject->CurrentCheckpointTransform = Transform;

    //SaveObject->ActiveCheckpoints.AddUnique(CheckpointID);
}

//AOriginCharacter* USaveManagerSubsystem::GetPlayerCharacter() const
//{
//    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//
//    if (!PC)
//    {
//        return nullptr;
//    }
//
//    return Cast<AOriginCharacter>(PC->GetPawn());
//}

//const FTransform& USaveManagerSubsystem::GetCheckpointTransform() const
//{
//    //return SaveObject->CurrentCheckpointTransform;
//}
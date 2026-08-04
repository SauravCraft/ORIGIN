#include "Subsystems/RespawnSubsystem.h"
#include "Actors/CheckpointBox.h"
#include "Subsystems/SaveManagerSubsystem.h"
#include "SaveGames/SaveGameData.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

void URespawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);


    if (USaveManagerSubsystem* Save =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        Save->OnGameSaved.AddUObject(
            this,
            &URespawnSubsystem::HandleSave);
        UE_LOG(LogTemp, Warning, TEXT("Binding Load Delegate"));
        Save->OnGameLoaded.AddUObject(
            this,
            &URespawnSubsystem::HandleLoad);

        UE_LOG(LogTemp, Warning, TEXT("Respawn Bound To Save Delegates"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Save Subsystem NOT FOUND"));
    }
}

void URespawnSubsystem::Deinitialize()
{
    Super::Deinitialize();

    UE_LOG(LogTemp, Log, TEXT("Respawn Subsystem Deinitialized"));
}

void URespawnSubsystem::SetCheckpoint(FTransform Checkpoint)
{

    if (!Checkpoint.IsValid())
    {
        return;
    }

    CurrentCheckpoint = Checkpoint;

    OnCheckpointActivated.Broadcast(CurrentCheckpoint);

    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Broadcast"));
}

bool URespawnSubsystem::RespawnPlayer(APawn* Pawn)
{
    if (!Pawn)
    {
        return false;
    }

    AController* Controller = Pawn->GetController();

    if (!Controller)
    {
        return false;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        return false;
    }

    FVector SpawnLocation = CurrentCheckpoint.GetLocation();
    FRotator SpawnRotation = CurrentCheckpoint.GetRotation().Rotator();

    Controller->UnPossess();

    if (Pawn)
    {
        Pawn->SetActorHiddenInGame(true);
        Pawn->SetActorEnableCollision(false);
        Pawn->DisableInput(nullptr);
        Pawn->SetLifeSpan(0.1f);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* NewPawn = World->SpawnActor<APawn>(
        Pawn->GetClass(),
        SpawnLocation,
        SpawnRotation,
        SpawnParams);
    UE_LOG(LogTemp, Warning,
        TEXT("Spawned Pawn At = %s"),
        *NewPawn->GetActorLocation().ToString());
    UE_LOG(LogTemp, Warning,
        TEXT("Respawning At = %s"),
        *CurrentCheckpoint.GetLocation().ToString());

    if (!NewPawn)
    {
        return false;
    }

    Controller->Possess(NewPawn);
    
    UE_LOG(LogTemp, Warning,
        TEXT("Pawn After Possess = %s"),
        *NewPawn->GetActorLocation().ToString());
    return true;
}



void URespawnSubsystem::HandleSave(
    USaveGameData* SaveGame)
{
    SaveGame->CurrentCheckpointTransform =
        CurrentCheckpoint;
    UE_LOG(LogTemp, Warning,
        TEXT("Saved Checkpoint = %s"),
        *CurrentCheckpoint.GetLocation().ToString());
}

void URespawnSubsystem::HandleLoad(
    USaveGameData* SaveGame)
{
    CurrentCheckpoint =
        SaveGame->CurrentCheckpointTransform;
    UE_LOG(LogTemp, Warning,
        TEXT("Loaded Checkpoint = %s"),
        *CurrentCheckpoint.GetLocation().ToString());
}
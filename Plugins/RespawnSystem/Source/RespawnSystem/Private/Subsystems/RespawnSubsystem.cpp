#include "Subsystems/RespawnSubsystem.h"
#include "Actors/CheckpointBox.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

void URespawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UE_LOG(LogTemp, Log, TEXT("Respawn Subsystem Initialized"));
}

void URespawnSubsystem::Deinitialize()
{
    Super::Deinitialize();

    UE_LOG(LogTemp, Log, TEXT("Respawn Subsystem Deinitialized"));
}

void URespawnSubsystem::SetCheckpoint(FTransform Checkpoint)
{
    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Called"));

    if (!Checkpoint.IsValid())
    {
        return;
    }

    CurrentCheckpoint = Checkpoint;

    OnCheckpointActivated.Broadcast(CurrentCheckpoint);

    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Activated"));
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

    if (!NewPawn)
    {
        return false;
    }

    Controller->Possess(NewPawn);
    
    UE_LOG(LogTemp, Warning, TEXT("Player Respawned"));

    return true;
}
#include "Subsystems/RespawnSubsystem.h"
#include "Interfaces/RespawnableInterface.h"
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

void URespawnSubsystem::SetCheckpoint(ACheckpointBox* Checkpoint)
{
    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Called"));

    if (!Checkpoint)
    {
        return;
    }

    CurrentCheckpoint = Checkpoint;

    OnCheckpointActivated.Broadcast(CurrentCheckpoint);

    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Activated"));
}

bool URespawnSubsystem::RespawnPlayer(APawn* Player)
{

    UE_LOG(LogTemp, Warning, TEXT("Player Respawned Called"));
    if (!Player || !Player->Implements<URespawnableInterface>())
    {
        return false;
    }

    if (!CurrentCheckpoint)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Active Checkpoint"));
        return false;
    }


    Player->SetActorLocationAndRotation(
        CurrentCheckpoint->GetActorLocation(),
        CurrentCheckpoint->GetActorRotation());

    OnPlayerRespawned.Broadcast(Player);

    UE_LOG(LogTemp, Warning, TEXT("Player Respawned"));

    return true;
}
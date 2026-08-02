// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/OriginGameMode.h"

void AOriginGameMode::RespawnPlayer(AController* PlayerController)
{
    UE_LOG(LogTemp, Warning, TEXT("RespawnPlayer() Called"));
	if (!PlayerController)  return ;

    FVector SpawnLocation = CurrentCheckpoint.GetLocation();
    FRotator SpawnRotation = CurrentCheckpoint.GetRotation().Rotator();

    APawn* OldPawn = PlayerController->GetPawn();

    PlayerController->UnPossess();

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(
        DefaultPawnClass,
        SpawnLocation,
        SpawnRotation,
        SpawnParams
    );

    if (NewPawn)
    {
        PlayerController->Possess(NewPawn);


        if (OldPawn)
        {
            OldPawn->SetActorHiddenInGame(true);
            OldPawn->SetActorEnableCollision(false);
            OldPawn->DisableInput(nullptr);

            OldPawn->SetLifeSpan(.001f);
            UE_LOG(LogTemp, Warning, TEXT("Player Respawned"));
        }
    }

    

}

void AOriginGameMode::SetCheckpoint(FTransform NewCheckpoint)
{
	CurrentCheckpoint = NewCheckpoint;
    UE_LOG(LogTemp, Warning, TEXT("Player Location set"));
}

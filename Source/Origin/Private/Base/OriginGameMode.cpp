#include "Base/OriginGameMode.h"
#include "Base/OriginCharacter.h"
#include "SaveSystem/SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

void AOriginGameMode::RespawnPlayer(AController* PlayerController)
{
    if (!PlayerController)
    {
        return;
    }

    USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();

    if (!SaveSubsystem)
    {
        return;
    }

    FTransform SpawnTransform =
        SaveSubsystem->GetCheckpointTransform();

    FVector SpawnLocation = SpawnTransform.GetLocation();
    FRotator SpawnRotation = SpawnTransform.GetRotation().Rotator();

    APawn* OldPawn = PlayerController->GetPawn();

    PlayerController->UnPossess();

    if (OldPawn)
    {
        OldPawn->SetActorHiddenInGame(true);
        OldPawn->SetActorEnableCollision(false);
        OldPawn->DisableInput(nullptr);
        OldPawn->SetLifeSpan(0.1f);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(
        DefaultPawnClass,
        SpawnLocation,
        SpawnRotation,
        SpawnParams);

    if (!NewPawn)
    {
        return;
    }

    PlayerController->Possess(NewPawn);


    UE_LOG(LogTemp, Warning, TEXT("Player Respawned"));
}
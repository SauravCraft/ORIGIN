#include "Actors/CheckpointBox.h"
#include "Subsystems/SaveManagerSubsystem.h"
#include "SaveGames/SaveGameData.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Subsystems/RespawnSubsystem.h"

ACheckpointBox::ACheckpointBox()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

    RootComponent = BoxComponent;

    BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
}

void ACheckpointBox::BeginPlay()
{
    Super::BeginPlay();

    BoxComponent->OnComponentBeginOverlap.AddDynamic(
        this,
        &ACheckpointBox::OnCheckpointBeginOverlap);
}

void ACheckpointBox::OnCheckpointBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor)
    {
        return;
    }

    APawn* Pawn = Cast<APawn>(OtherActor);

    if (!Pawn || bIsActivated || !Pawn->IsPlayerControlled())
    {
        return;
    }


    bIsActivated = true;

    if (URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>())
    {
        Respawn->SetCheckpoint(Pawn->GetActorTransform());
    }

    if (USaveManagerSubsystem* Save =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        Save->SaveGame();
    }

    UE_LOG(LogTemp, Warning, TEXT("CheckPoint Hit!"));

}
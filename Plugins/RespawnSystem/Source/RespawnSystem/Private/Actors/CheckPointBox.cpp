#include "Actors/CheckpointBox.h"
#include "Subsystems/SaveManagerSubsystem.h"
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


    // Restore CheckPoints

    if (URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>())
    {
        bIsActivated = Respawn->IsCheckpointActivated(CheckPointId);

        if (bIsActivated)
        {
            // Restore visuals
        }

    }

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
    APawn* Pawn = Cast<APawn>(OtherActor);

    if (!Pawn || !Pawn->IsPlayerControlled() || bIsActivated)
    {
        return;
    }

    URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>();

    if (!Respawn)
    {
        return;
    }

    if (Respawn->IsCheckpointActivated(CheckPointId))
    {
        return;
    }


    Respawn->ActivateCheckpoint(CheckPointId);
    bIsActivated = true;

    Respawn->SetCheckpoint(Pawn->GetActorTransform());

    UE_LOG(LogTemp, Warning,
        TEXT("Checkpoint %s Activated"),
        *CheckPointId.ToString());
}
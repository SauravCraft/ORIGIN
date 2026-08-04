#include "Actors/CheckpointBox.h"
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


    if (URespawnSubsystem* RespawnSubsystem =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>())
    {
        bIsActivated = true;
        RespawnSubsystem->SetCheckpoint(Pawn->GetActorTransform());
    }

    UE_LOG(LogTemp, Warning, TEXT("CheckPoint Hit!"));

}
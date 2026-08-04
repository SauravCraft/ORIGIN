#include "Actors/CheckpointBox.h"
#include "Interfaces/RespawnableInterface.h"
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

    if (!OtherActor->Implements<URespawnableInterface>())
    {
        return;
    }

    const bool bCanActivate =
        IRespawnableInterface::Execute_CanActivateCheckpoint(OtherActor);

    if (!bCanActivate)
    {
        return;
    }

    if (URespawnSubsystem* RespawnSubsystem =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>())
    {
        RespawnSubsystem->SetCheckpoint(this);
    }

    UE_LOG(LogTemp, Warning, TEXT("CheckPoint Hit!"));

}
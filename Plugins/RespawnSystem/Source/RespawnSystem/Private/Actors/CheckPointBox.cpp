#include "Actors/CheckpointBox.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "RespawnSubsystem.h"

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
    APawn* Pawn = Cast<APawn>(OtherActor);

    if (!Pawn)
    {
        return;
    }

    if (UGameInstance* GI = GetGameInstance())
    {
        if (URespawnSubsystem* RespawnSubsystem =
            GI->GetSubsystem<URespawnSubsystem>())
        {
            RespawnSubsystem->SetCheckpoint(this);
        }
    }
}
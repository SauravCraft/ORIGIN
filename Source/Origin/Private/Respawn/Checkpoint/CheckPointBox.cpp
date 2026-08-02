#include "Respawn/Checkpoint/CheckPointBox.h"
#include "Base/OriginCharacter.h"
#include "SaveSystem/OriginSaveGame.h"
#include "SaveSystem/SaveManagerSubsystem.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckPointBox::ACheckPointBox()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ACheckPointBox::BeginPlay()
{
    Super::BeginPlay();

    CollisionBox->OnComponentBeginOverlap.AddDynamic(
        this,
        &ACheckPointBox::OnOverlapBegin);

    USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();

    if (!SaveSubsystem)
    {
        return;
    }

    if (SaveSubsystem->GetSaveObject()->ActiveCheckpoints.Contains(CheckpointID))
    {
        bActiveCheckPoint = true;

        // TODO:
        // Activate your checkpoint VFX / Mesh / Material here
    }
}

void ACheckPointBox::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    AOriginCharacter* Player = Cast<AOriginCharacter>(OtherActor);

    if (!Player || bActiveCheckPoint)
    {
        return;
    }

    USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();

    if (!SaveSubsystem)
    {
        return;
    }

    bActiveCheckPoint = true;

    FTransform SpawnTransform = GetActorTransform();
    SpawnTransform.SetRotation(Player->GetActorQuat());

    SaveSubsystem->SetCurrentCheckpoint(
        CheckpointID,
        SpawnTransform);

    SaveSubsystem->SaveGame();

    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Activated : %s"),
        *CheckpointID.ToString());
}
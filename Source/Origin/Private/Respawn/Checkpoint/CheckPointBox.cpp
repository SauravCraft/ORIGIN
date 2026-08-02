// Fill out your copyright notice in the Description page of Project Settings.
#include "Respawn/Checkpoint/CheckPointBox.h"
#include "SaveSystem/OriginSaveGame.h"
#include "Base/OriginGameMode.h"
#include "Base/OriginCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckPointBox::ACheckPointBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionBox =
        CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

    RootComponent = CollisionBox;

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

}

// Called when the game starts or when spawned
void ACheckPointBox::BeginPlay()
{
    Super::BeginPlay();

    CollisionBox->OnComponentBeginOverlap.AddDynamic(
        this,
        &ACheckPointBox::OnOverlapBegin);

    if (UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSave"), 0))
    {
        SaveObject = Cast<UOriginSaveGame>(
            UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSave"), 0));
    }
    else
    {
        SaveObject = Cast<UOriginSaveGame>(
            UGameplayStatics::CreateSaveGameObject(UOriginSaveGame::StaticClass()));
    }

    if (!SaveObject)
    {
        return;
    }

    bActiveCheckPoint =
        SaveObject->ActiveCheckpoints.Contains(CheckpointID);
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

    AOriginGameMode* GM =
        Cast<AOriginGameMode>(UGameplayStatics::GetGameMode(this));

    if (!GM || !SaveObject)
    {
        return;
    }

    bActiveCheckPoint = true;

    SaveObject->ActiveCheckpoints.AddUnique(CheckpointID);

    FTransform CheckpointTransform = GetActorTransform();
    CheckpointTransform.SetRotation(Player->GetActorQuat());

    GM->SetCheckpoint(CheckpointTransform);

    SaveObject->PlayerLocation = Player->GetActorLocation();
    SaveObject->PlayerRotation = Player->GetActorRotation();

    UGameplayStatics::SaveGameToSlot(
        SaveObject,
        TEXT("PlayerSave"),
        0);

    UE_LOG(LogTemp, Warning, TEXT("Checkpoint Saved"));
}



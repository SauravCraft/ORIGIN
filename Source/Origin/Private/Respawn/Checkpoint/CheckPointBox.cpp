// Fill out your copyright notice in the Description page of Project Settings.
#include "Respawn/Checkpoint/CheckPointBox.h"
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
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckPointBox::OnOverlapBegin);

}

void ACheckPointBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    // Save Transform
    AOriginCharacter* Player = Cast<AOriginCharacter>(OtherActor);
    if (!Player || bActiveCheckPoint) return;

    bActiveCheckPoint = true;

    AOriginGameMode* GM = Cast<AOriginGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM) return;


    FTransform CheckpointTransform = GetActorTransform();

    // Replace only the rotation
    CheckpointTransform.SetRotation(Player->GetActorQuat());

    GM->SetCheckpoint(CheckpointTransform);






}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Respawn/DeathPoint/DeathBox.h"
#include "Base/OriginCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeathBox::ADeathBox()
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
void ADeathBox::BeginPlay()
{
	Super::BeginPlay();
	
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathBox::OnOverlapBegin);

}

void ADeathBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Call Death in Character

    AOriginCharacter* Player = Cast<AOriginCharacter>(OtherActor);
    if (!Player) return;

    Player->Die();










}



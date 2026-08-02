// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction/BaseActor/BaseActor.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseActor::Interact_Implementation()
{

    GEngine->AddOnScreenDebugMessage(
        -1,
        2.f,
        FColor::Green,
        TEXT("Interacted")
    );

}

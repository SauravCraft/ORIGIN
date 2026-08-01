// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Items/Door.h"

void ADoor::Interact_Implementation()
{

    GEngine->AddOnScreenDebugMessage(
        -1,
        2.f,
        FColor::Green,
        TEXT("Door Opened")
    );

}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interface/Interactable.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

class UItemData;

UCLASS()
class ORIGIN_API ABaseActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();


	virtual void Interact_Implementation() override;
};

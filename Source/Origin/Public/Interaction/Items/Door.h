// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interface/Interactable.h"
#include "Interaction/BaseActor/BaseActor.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class ORIGIN_API ADoor : public ABaseActor,public IInteractable
{
	GENERATED_BODY()
	

public:
	virtual void Interact_Implementation() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OriginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AOriginGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer(AController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void SetCheckpoint(FTransform NewCheckpoint);

	UPROPERTY(BlueprintReadWrite)
	FTransform CurrentCheckpoint;

};

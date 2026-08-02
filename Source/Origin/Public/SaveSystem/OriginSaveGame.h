// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OriginSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ORIGIN_API UOriginSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite)
    FVector PlayerLocation;

    UPROPERTY(BlueprintReadWrite)
    FRotator PlayerRotation;

    UPROPERTY(BlueprintReadWrite)
    float Health = 100.f;
	
};

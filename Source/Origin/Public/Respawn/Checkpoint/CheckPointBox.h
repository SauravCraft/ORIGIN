// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointBox.generated.h"


class UBoxComponent;
class UOriginSaveGame;


UCLASS()
class ORIGIN_API ACheckPointBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPointBox();

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    bool bActiveCheckPoint = false;

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    int32 CheckpointID;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint")
    int32 CurrentCheckpoint;

    UPROPERTY()
    UOriginSaveGame* SaveObject = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UBoxComponent> CollisionBox;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );


};

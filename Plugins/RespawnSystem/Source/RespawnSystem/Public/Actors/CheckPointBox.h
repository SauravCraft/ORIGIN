#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointBox.generated.h"

class UBoxComponent;

UCLASS()
class RESPAWNSYSTEM_API ACheckpointBox : public AActor
{
    GENERATED_BODY()

public:
    ACheckpointBox();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnCheckpointBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    bool bIsActivated = false;

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Checkpoint")
    TObjectPtr<UBoxComponent> BoxComponent;
};
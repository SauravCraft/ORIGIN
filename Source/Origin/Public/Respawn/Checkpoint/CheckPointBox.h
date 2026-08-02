#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointBox.generated.h"

class UBoxComponent;

UCLASS()
class ORIGIN_API ACheckPointBox : public AActor
{
    GENERATED_BODY()

public:
    ACheckPointBox();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

private:

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    FName CheckpointID;

    UPROPERTY()
    bool bActiveCheckPoint = false;
};
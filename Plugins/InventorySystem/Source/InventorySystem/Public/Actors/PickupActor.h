#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UItemData;

UCLASS()
class INVENTORYSYSTEM_API APickupActor : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    APickupActor();

protected:
    virtual void BeginPlay() override;

    //UFUNCTION()
    //void OnSphereBeginOverlap(
    //    UPrimitiveComponent* OverlappedComponent,
    //    AActor* OtherActor,
    //    UPrimitiveComponent* OtherComp,
    //    int32 OtherBodyIndex,
    //    bool bFromSweep,
    //    const FHitResult& SweepResult);

public:

    // Implement Interface for Interact
    virtual void Interact_Implementation(AActor* Interactor) override;

    /** Mesh */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UStaticMeshComponent> Mesh;

    /** Pickup Collision */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USphereComponent> Sphere;

    /** Item Definition */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UItemData> ItemData;

    /** Stack Size */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 Quantity = 1;
};
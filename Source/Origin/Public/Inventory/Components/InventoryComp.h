// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComp.generated.h"

class UItemObject;
class UItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORIGIN_API UInventoryComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComp();


	UFUNCTION(BlueprintCallable)
	void AddItem(UItemData* ItemData, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool RemoveItemByData(UItemData* ItemData, int32 Quantity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemObject>> Items;

public:	

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;



		
};

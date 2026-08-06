// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "ItemsData/ItemObject.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


bool UInventoryComponent::AddItem(UItemData* ItemData, int32 Quantity)
{
    if (!ItemData)
    {
        return false;
    }

    UItemObject* NewItem = NewObject<UItemObject>(this);

    NewItem->ItemData = ItemData;
    NewItem->Quantity = Quantity;
    NewItem->Durability = 100.f;

    Items.Add(NewItem);

    OnInventoryChanged.Broadcast();
    return true;
}

bool UInventoryComponent::RemoveItemByData(UItemData* ItemData, int32 Quantity)
{
    if (!ItemData)
    {
        return false;
    }

    for (int32 i = 0; i < Items.Num(); ++i)
    {
        UItemObject* Item = Items[i];

        if (Item && Item->ItemData == ItemData)
        {
            Item->Quantity -= Quantity;

            if (Item->Quantity <= 0)
            {
                Items.RemoveAt(i);
            }

            OnInventoryChanged.Broadcast();
            return true;
        }
    }

    return false;
}


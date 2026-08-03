#pragma once

#include "CoreMinimal.h"
#include "Interaction/BaseActor/BaseActor.h"
#include "PickupItem.generated.h"

class UItemData;

UCLASS()
class ORIGIN_API APickupItem : public ABaseActor
{
    GENERATED_BODY()

public:
    APickupItem();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
    TObjectPtr<UItemData> ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
    int32 Quantity = 1;
};
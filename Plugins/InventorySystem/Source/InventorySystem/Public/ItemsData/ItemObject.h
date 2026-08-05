#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

class UItemData;

UCLASS(BlueprintType)
class ORIGIN_API UItemObject : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UItemData> ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Durability = 100.f;
};
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UCLASS(BlueprintType)
class INVENTORYSYSTEM_API UItemData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UTexture2D* Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 MaxStack = 99;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Weight = 1.f;
};
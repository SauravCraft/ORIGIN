#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/Interactable.h"

#include "HighlightableMeshComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API  UHighlightableMeshComponent : public UStaticMeshComponent , public IInteractable
{
    GENERATED_BODY()

public:

    UHighlightableMeshComponent();

    UFUNCTION(BlueprintCallable)
    virtual void Highlight_Implementation() override;

    UFUNCTION(BlueprintCallable)
    virtual void UnHighlight_Implementation() override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Highlight")
    TObjectPtr<UMaterialInterface> HighlightMaterial;
};
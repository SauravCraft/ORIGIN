#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interface/Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "HighlightableMeshComp.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ORIGIN_API UHighlightableMeshComponent : public UStaticMeshComponent , public IInteractable
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
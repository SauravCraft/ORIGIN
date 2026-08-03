#include "Components/HighlightableMeshComp.h"

UHighlightableMeshComponent::UHighlightableMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHighlightableMeshComponent::Highlight_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Highlight Called"));
    SetOverlayMaterial(HighlightMaterial);
}

void UHighlightableMeshComponent::UnHighlight_Implementation()
{
    SetOverlayMaterial(nullptr);
    UE_LOG(LogTemp, Warning, TEXT("UnHighlight Called"));
}
#include "Subsystems/InteractionSubsystem.h"
#include "Components/InteractionComponent.h"
#include "GameFramework/Pawn.h"

void UInteractionSubsystem::Interact(APawn* PlayerPawn)
{
    if (!PlayerPawn)
    {
        return;
    }

    if (UInteractionComponent* IC =
        PlayerPawn->FindComponentByClass<UInteractionComponent>())
    {
        IC->Interaction();
    }
}
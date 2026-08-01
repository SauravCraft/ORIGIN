#include "Base/OriginCharacter.h"
#include "Engine/CollisionProfile.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/Interface/Interactable.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"

AOriginCharacter::AOriginCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	// Make it the Root
	SetRootComponent(CapsuleComponent);

	// Size
	CapsuleComponent->InitCapsuleSize(30.f, 86.f);

	// Collision
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Optional
	CapsuleComponent->SetGenerateOverlapEvents(true);
	// CapsuleComponent->CanCharacterStepUpOn = ECB_Yes;
}

void AOriginCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateInteractable();

}


void AOriginCharacter::BeginPlay()
{

	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (!PC) return;
		ULocalPlayer* LP = PC->GetLocalPlayer();
			if (!LP) return;
			UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			if (!Subsystem) return;
			
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

void AOriginCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInput) return;

	// Binding Input Function 
	EnhancedInput->BindAction(
		InteractAction,
		ETriggerEvent::Started,
		this,
		&AOriginCharacter::Interaction);


}

void AOriginCharacter::UpdateInteractable()
{
    APlayerController* PC = Cast<APlayerController>(GetController());

    if (!PC)
    {
        return;
    }

    int32 ViewportX, ViewportY;
    PC->GetViewportSize(ViewportX, ViewportY);

    FVector WorldLocation;
    FVector WorldDirection;

    if (!PC->DeprojectScreenPositionToWorld(
        ViewportX * 0.5f,
        ViewportY * 0.5f,
        WorldLocation,
        WorldDirection))
    {
        return;
    }

    FVector Start = WorldLocation;
    FVector End = Start + WorldDirection * InteractionDistance;

    FHitResult Hit;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        Start,
        End,
        ECC_Visibility,
        Params
    );

    AActor* NewInteractable = nullptr;

    if (bHit)
    {
        AActor* HitActor = Hit.GetActor();

        if (HitActor && HitActor->Implements<UInteractable>())
        {
            NewInteractable = HitActor;
        }
    }

    if (NewInteractable == CurrentInteractable)
    {
        return;
    }

    if (CurrentInteractable)
    {
        if (UActorComponent* Highlightable = CurrentInteractable->FindComponentByInterface(UInteractable::StaticClass());IsValid(Highlightable))
        {
            IInteractable::Execute_UnHighlight(Highlightable);
        }
    }

    CurrentInteractable = NewInteractable;

    if (CurrentInteractable)
    {
        if (UActorComponent* Highlightable = CurrentInteractable->FindComponentByInterface(UInteractable::StaticClass());IsValid(Highlightable))
        {
            IInteractable::Execute_Highlight(Highlightable);
        }
    }
}



void AOriginCharacter::Interaction(const FInputActionValue& Value)
{
    if (!CurrentInteractable)
    {
        return;
    }
    IInteractable::Execute_Interact(CurrentInteractable);
}
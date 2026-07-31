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


void AOriginCharacter::Interaction(const FInputActionValue& Value)
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

    PC->DeprojectScreenPositionToWorld(
        ViewportX * 0.5f,
        ViewportY * 0.5f,
        WorldLocation,
        WorldDirection
    );

    FVector Start = WorldLocation;
    FVector End = Start + WorldDirection * 300.f;

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

    DrawDebugLine(
        GetWorld(),
        Start,
        End,
        FColor::Red,
        false,
        2.f,
        0,
        1.f
    );

    if (!bHit)
        return;

    AActor* HitActor = Hit.GetActor();

    if (!HitActor)
        return;

    IInteractable* Interactable =
        Cast<IInteractable>(HitActor);

    if (Interactable)
    {
        Interactable->Interact();
    }
}
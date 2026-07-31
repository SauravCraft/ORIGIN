#include "Base/OriginCharacter.h"
#include "Engine/CollisionProfile.h"

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
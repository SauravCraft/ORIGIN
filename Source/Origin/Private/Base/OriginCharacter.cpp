#include "Base/OriginCharacter.h"

#include "Base/OriginGameMode.h"
#include "SaveGames/SaveGameData.h"
#include "Subsystems/SaveManagerSubsystem.h"
#include "Subsystems/RespawnSubsystem.h"
#include "Components/InteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"

AOriginCharacter::AOriginCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

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

    if (USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        SaveSubsystem->OnGameLoaded.AddUObject(
            this,
            &AOriginCharacter::HandleLoad);

        SaveSubsystem->OnGameSaved.AddUObject(
            this,
            &AOriginCharacter::HandleSave);


        SaveSubsystem->LoadGame();
    }

}

void AOriginCharacter::interact()
{
    UInteractionComponent* IC = FindComponentByClass<UInteractionComponent>();

    if (!IC) return;

    IC->Interaction();

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
        &AOriginCharacter::interact);

    EnhancedInput->BindAction(
        LoadAction,
        ETriggerEvent::Started,
        this,
        &AOriginCharacter::LoadGameTest);


        EnhancedInput->BindAction(
        SaveAction,
        ETriggerEvent::Started,
        this,
        &AOriginCharacter::SaveGameTest);


}

void AOriginCharacter::SaveGameTest()
{
    USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();

    if (SaveSubsystem)
    {
        SaveSubsystem->SaveGame();
    }
}

void AOriginCharacter::LoadGameTest()
{
    USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();

    if (SaveSubsystem)
    {
        SaveSubsystem->LoadGame();
    }

}


void AOriginCharacter::HandleSave(USaveGameData* SaveGame)
{
    SaveGame->PlayerTransform = GetActorTransform();
}

void AOriginCharacter::HandleLoad(USaveGameData* SaveGame)
{
    URespawnSubsystem* Respawn =
        GetGameInstance()->GetSubsystem<URespawnSubsystem>();
    if (!Respawn) return;

    Respawn->RespawnPlayer(this, SaveGame->PlayerTransform);
}

#include "Base/OriginCharacter.h"

#include "Base/OriginGameMode.h"
#include "SaveSystem/SaveManagerSubsystem.h"
#include "Components/InteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"

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
}

//void AOriginCharacter::Die()
//{
//    
//    AOriginGameMode* GM = Cast<AOriginGameMode>(UGameplayStatics::GetGameMode(this));
//    if (!GM) return;
//    GM->RespawnPlayer(GetController());
//
//
//}


void AOriginCharacter::BeginPlay()
{

	Super::BeginPlay(); 

    if (USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        SaveSubsystem->LoadGame();
    }

    GetWorldTimerManager().SetTimer(
        AutoSaveTimer,
        this,
        &AOriginCharacter::AutoSave,
        100.0f,
        true);


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
        SaveAction,
        ETriggerEvent::Triggered,
        this,
        &AOriginCharacter::SaveGameTest);

    EnhancedInput->BindAction(
        LoadAction,
        ETriggerEvent::Triggered,
        this,
        &AOriginCharacter::LoadGameTest);


}


void AOriginCharacter::AutoSave()
{
    if (USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
        SaveSubsystem->SaveGame();

        UE_LOG(LogTemp, Warning, TEXT("Auto Saved"));
    }
}

void AOriginCharacter::interact()
{
    UInteractionComponent* IC = FindComponentByClass<UInteractionComponent>();
    
    if (!IC) return;

    IC->Interaction();

}


bool AOriginCharacter::CanActivateCheckpoint_Implementation() const
{
    return true;
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
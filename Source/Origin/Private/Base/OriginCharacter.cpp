#include "Base/OriginCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Base/OriginGameMode.h"
#include "SaveSystem/SaveManagerSubsystem.h"
#include "Engine/CollisionProfile.h"
#include "Interaction/Items/PickupItem.h"
#include "Inventory/Components/InventoryComp.h"
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

void AOriginCharacter::Die()
{
    
    AOriginGameMode* GM = Cast<AOriginGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM) return;
    GM->RespawnPlayer(GetController());


}


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
		&AOriginCharacter::Interaction);

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

    UInventoryComp* InvComp = FindComponentByClass<UInventoryComp>();

    if (!InvComp)
    {
        return;
    }

    APickupItem* Pickup = Cast<APickupItem>(CurrentInteractable);

    if (!Pickup || !Pickup->ItemData)
    {
        return;
    }
    InvComp->AddItem(Pickup->ItemData, Pickup->Quantity);

    Pickup->Destroy();


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
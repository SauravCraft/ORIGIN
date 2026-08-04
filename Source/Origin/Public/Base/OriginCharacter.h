#pragma once

#include "CoreMinimal.h"
#include "Interfaces/RespawnableInterface.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "OriginCharacter.generated.h"

class UInputAction;

UCLASS(Blueprintable)
class ORIGIN_API AOriginCharacter : public APawn, public IRespawnableInterface
{
	GENERATED_BODY()

public:
	AOriginCharacter();

	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//void Die();

	UFUNCTION(BlueprintCallable)
	void SaveGameTest();

	UFUNCTION(BlueprintCallable)
	void LoadGameTest();

	FTimerHandle AutoSaveTimer;

	void AutoSave();

	// Interaction function for Calling Interaction function inside Plugins

	UFUNCTION()
	void interact();

	// For Checking Checkpoint Activator Or Not

	virtual bool CanActivateCheckpoint_Implementation() const override;


protected:

	/** Root Capsule */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;


	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Actions 

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SaveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LoadAction;


};
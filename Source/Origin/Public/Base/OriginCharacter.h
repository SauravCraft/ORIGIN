#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "OriginCharacter.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS(Blueprintable)
class ORIGIN_API AOriginCharacter : public APawn
{
	GENERATED_BODY()

public:
	AOriginCharacter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void SaveGameTest();

	UFUNCTION(BlueprintCallable)
	void LoadGameTest();

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


	void UpdateInteractable();

	void Interaction(const FInputActionValue& Value);


private:

	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionDistance = 300.f;


};
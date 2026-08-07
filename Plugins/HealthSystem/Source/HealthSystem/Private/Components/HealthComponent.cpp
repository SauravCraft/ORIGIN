// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Interfaces/Damagable.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	CurrentHealth = MaxHealth;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* Damagable, const float& Damage)
{
	if (!Damagable || Damage <= 0 ) return;

	//Damagable->Implements<UDamagable>();
	CurrentHealth -= Damage;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("%s Health: %.0f"),
		*GetOwner()->GetName(),
		CurrentHealth);

	OnHealthChange.Broadcast();

	if (CurrentHealth <= 0)
	{
		Kill();
	}

}

void UHealthComponent::Kill()
{
	OnDeath.Broadcast();
}


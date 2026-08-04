#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"

class URespawnSubsystem;

UCLASS(ClassGroup = (Respawn), meta = (BlueprintSpawnableComponent))
class RESPAWNSYSTEM_API URespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URespawnComponent();

protected:
    virtual void BeginPlay() override;

public:
    /** Respawn the owner */
    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void RespawnOwner();

private:
    UPROPERTY()
    TObjectPtr<URespawnSubsystem> RespawnSubsystem;
};
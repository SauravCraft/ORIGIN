// HealthEnums.h

#pragma once

#include "HealthEnums.generated.h"

UENUM(BlueprintType)
enum class EDeathState : uint8
{
    Alive,      
    Dead,      
    Respawning 
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    Physical, 
    Fire,
    Poison, 
    Fall
};
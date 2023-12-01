#pragma once

#include "CoreMinimal.h"
#include "AbilitySlot.generated.h"

UENUM( BlueprintType )
enum class EAbilitySlot : uint8
{
	First        UMETA( DisplayName = "First" ),
	Second       UMETA( DisplayName = "Second" ),
	Third        UMETA( DisplayName = "Third" ),
	Ultimate     UMETA( DisplayName = "Ultimate" ),
	AutoAttack   UMETA( DisplayName = "Auto-Attack" ),
	Passive      UMETA( DisplayName = "Passive" ),
};
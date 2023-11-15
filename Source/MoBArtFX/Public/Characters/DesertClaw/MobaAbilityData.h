#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MobaAbilityData.generated.h"

class UMobaAbility;

UENUM( BlueprintType )
enum class EMobaAbilitySlot : uint8
{
	First        UMETA( DisplayName = "First" ),
	Second       UMETA( DisplayName = "Second" ),
	Third        UMETA( DisplayName = "Third" ),
	Ultimate     UMETA( DisplayName = "Ultimate" ),
	AutoAttack   UMETA( DisplayName = "Auto-Attack" ),
	Passive      UMETA( DisplayName = "Passive" ),
};

UENUM( BlueprintType )
enum class EMobaAbilityMode : uint8
{
	/*
	 *  Ability is designed to be run once per input
	 */
	Single       UMETA( DisplayName = "Single" ),
	/*
	 *  Ability is designed to have both active and inactive states for more than one frame time.
	 *  In the Ability Data, can be coupled with 'Input/Is Holded' to bind the state to a key hold instead of double input
	 */
	OnOff        UMETA( DisplayName = "On/Off" ),
};

/*
 *	Ability Data
 */
UCLASS()
class MOBARTFX_API UMobaAbilityData : public UDataAsset
{
	GENERATED_BODY()

public:
	//  Label name
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Base" )
	FString Name = "N/A";

	//  Class to instantiate on BeginPlay
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Base" )
	TSubclassOf<UMobaAbility> Class;

	//  Cooldown applied after ability run
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Base" )
	float Cooldown = 5.0f;

	//  Cooldown applied after ability becomes active. 'Mode' must be set to 'On Off'
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Base", meta = ( EditCondition = "Mode == EMobaAbilityMode::OnOff" ) )
	float ToggleCooldown = 1.0f;

	//  Mode of run
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Base" )
	EMobaAbilityMode Mode = EMobaAbilityMode::Single;

	//  If set, the input key can be holded instead of pressed. 'Mode' must be set to 'On Off'
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Input", meta = ( EditCondition = "Mode == EMobaAbilityMode::OnOff" ) )
	bool IsHolded = false;

	//  Should a slot be overriden when the ability is active. 'Mode' must be set to 'On Off'
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Input", meta = ( EditCondition = "Mode == EMobaAbilityMode::OnOff" ) )
	bool UseActiveOverrideSlot = false;

	//  Slot to provide an additional input
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Input", meta = ( EditCondition = "UseActiveOverrideSlot" ) )
	EMobaAbilitySlot ActiveOverrideSlot = EMobaAbilitySlot::First;
};
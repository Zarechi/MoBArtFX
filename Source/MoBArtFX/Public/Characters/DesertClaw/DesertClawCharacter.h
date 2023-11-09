#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MobaAbility.h"
#include "DesertClawPlayerInfos.h"
#include "DesertClawPlayerController.h"
#include "DesertClawCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API ADesertClawCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	void OverrideAbilitySlot( EMobaAbilitySlot slot, UMobaAbility* ability );
	void ResetAbilitySlot( EMobaAbilitySlot slot );

	void ProcessAbility( EMobaAbilitySlot slot, bool is_started );

	UFUNCTION( BlueprintCallable, BlueprintPure )
	UMobaAbility* GetAbility( EMobaAbilitySlot slot );

	UFUNCTION( BlueprintCallable, BlueprintPure )
	ADesertClawPlayerController* GetPlayerController() { return PlayerController; }

protected:
	void BeginPlay() override;
	void Tick( float dt ) override;
	
	void InitializeAbilities();
	UMobaAbility* CreateAbility( EMobaAbilitySlot slot, UMobaAbilityData* data );

	void Death_Implementation() override;

	/*
	void AutoAttack_Implementation() override;
	void Reload_Implementation() override;

	void Spell_01_Implementation() override;
	void Spell_02_Implementation() override;
	void Ultimate_Implementation() override;
	*/

	UPROPERTY()
	TMap<EMobaAbilitySlot, UMobaAbility*> Abilities;
	TMap<EMobaAbilitySlot, UMobaAbility*> InputsToAbilities;

	TObjectPtr<UDesertClawPlayerInfos> Data;

	ADesertClawPlayerController* PlayerController;
};

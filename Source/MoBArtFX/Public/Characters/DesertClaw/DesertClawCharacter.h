#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "DesertClawPlayerInfos.h"
#include "MobaAbility.h"
#include "DesertClawCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API ADesertClawCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:


protected:
	void BeginPlay() override;
	void Tick( float dt ) override;
	
	void InitializeAbilities();
	UMobaAbility* CreateAbility( EMobaAbilitySlot slot, UMobaAbilityData* data );

	void Death_Implementation() override;

	void AutoAttack_Implementation() override;
	void Reload_Implementation() override;

	void Spell_01_Implementation() override;
	void Spell_02_Implementation() override;
	void Ultimate_Implementation() override;

	UPROPERTY()
	TMap<EMobaAbilitySlot, UMobaAbility*> Abilities;
	TMap<EMobaAbilitySlot, UMobaAbility*> InputsToAbilities;

	TObjectPtr<UDesertClawPlayerInfos> Data;
};

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "DesertClawPlayerInfos.h"
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
	/*UMobaAbility* CreateAbility( kMobaAbilitySlot slot, UMobaAbilityData* data );

	UPROPERTY()
	TMap<kMobaAbilitySlot, UMobaAbility*> Abilities;
	TMap<kMobaAbilitySlot, UMobaAbility*> InputsToAbilities;*/
};

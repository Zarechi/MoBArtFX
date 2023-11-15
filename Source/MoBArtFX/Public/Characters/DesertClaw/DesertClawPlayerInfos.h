#pragma once

#include "CoreMinimal.h"
#include "PlayerInfos.h"
#include "MobaAbilityData.h"
#include "DesertClawPlayerInfos.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API UDesertClawPlayerInfos : public UPlayerInfos
{
	GENERATED_BODY()
	
public:
	//  Abilities
	UPROPERTY( EditAnywhere, Category = "Abilities" )
	TMap<EMobaAbilitySlot, UMobaAbilityData*> Abilities;
};

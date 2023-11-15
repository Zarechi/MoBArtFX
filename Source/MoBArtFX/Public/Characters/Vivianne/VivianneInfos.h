

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInfos.h"
#include "VivianneInfos.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API UVivianneInfos : public UPlayerInfos
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|AutoAttack")
	double healingAmount = 150.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Primary")
	double poisonAmount = 150.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary")
	double sprintDuration = 150.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary")
	double sprintSpeed = 150.f;
};

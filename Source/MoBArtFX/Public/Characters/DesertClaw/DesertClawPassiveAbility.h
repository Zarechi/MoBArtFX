#pragma once

#include "CoreMinimal.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "DesertClawPassiveAbility.generated.h"

/*
 *	Passive Ability Data
 */
UCLASS()
class MOBARTFX_API UDesertClawPassiveAbilityData : public UMobaAbilityData
{
	GENERATED_BODY()

public:
	//  How much sand percentage do you gain each second?
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Passive" )
	float SandGainRate = 0.1f;
};

/**
 * 
 */
UCLASS()
class MOBARTFX_API UDesertClawPassiveAbility : public UMobaAbility
{
	GENERATED_BODY()
	
public:
	void OnInitialize_Implementation() override;
	void OnTick_Implementation( float dt ) override;

	/*
	 * Add, or remove if negative, the provided amount of sand. Sand amount is clamped from 0.0 to 1.0
	 * @param amount Amount of range -1.0 to 1.0; If negative, sand will be removed otherwise it's added
	 */
	UFUNCTION( BlueprintCallable, Category = "Passive" )
	void AddSandPercent( float amount );

	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Passive" )
	bool CanAffordSand( float amount );

	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Passive" )
	float GetSandPercent() { return SandPercent; }

	void UpdateSandHUD();

private:
	float SandPercent { 1.0f };

	//UMobaDesertClawHUDWidget* ChampionWidget;
	UDesertClawPassiveAbilityData* CustomData;
};

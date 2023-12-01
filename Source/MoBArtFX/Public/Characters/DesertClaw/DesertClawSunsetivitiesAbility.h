#pragma once

#include "CoreMinimal.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "Characters/DesertClaw/DesertClawSunsetivitiesGrenade.h"
#include "Characters/DesertClaw/DesertClawSunsetivitiesShield.h"
#include "DesertClawSunsetivitiesAbility.generated.h"

/*
 *	Ability Data
 */
UCLASS()
class MOBARTFX_API UDesertClawSunsetivitiesAbilityData : public UMobaAbilityData
{
	GENERATED_BODY()

public:
	//  Distance of initial throw
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Sunsetivities" )
	float ThrowDistance = 15.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Sunsetivities" )
	FVector ThrowImpulseOffset { 0.0f, 0.0f, 2.0f };

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Sunsetivities" )
	float ThrowImpulseForce = 5000.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Sunsetivities" )
	TSubclassOf<ADesertClawSunsetivitiesGrenade> GrenadeActorClass;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Sunsetivities" )
	TSubclassOf<ADesertClawSunsetivitiesShield> ShieldActorClass;
};

/**
 * 
 */
UCLASS()
class MOBARTFX_API UDesertClawSunsetivitiesAbility : public UMobaAbility
{
	GENERATED_BODY()
	
public:
	void OnInitialize_Implementation() override;
	void OnRun_Implementation( FMobaAbilityRunContext context ) override;

private:
	UDesertClawSunsetivitiesAbilityData* CustomData;
	
};

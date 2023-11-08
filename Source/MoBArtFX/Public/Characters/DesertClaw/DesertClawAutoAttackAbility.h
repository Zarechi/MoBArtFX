#pragma once

#include "CoreMinimal.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DesertClawAutoAttackAbility.generated.h"


/*
 *	Ability Data
 */
UCLASS()
class MOBARTFX_API UDesertClawAutoAttackAbilityData : public UMobaAbilityData
{
	GENERATED_BODY()

public:
	//  Max Range of auto-attack
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float Range = 750.0f;

	//  Damage per second
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float Damage = 50.0f;

	//  Radius of sphere trace
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float Radius = 15.0f;

	//  Trace query object types
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryObjectTypes;

	//  Trace draw debug type
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
};

/**
 * 
 */
UCLASS()
class MOBARTFX_API UDesertClawAutoAttackAbility : public UMobaAbility
{
	GENERATED_BODY()
	
public:
	void OnInitialize_Implementation() override;
	void OnTick_Implementation( float dt ) override;
	void OnRun_Implementation( FMobaAbilityRunContext context ) override;
	void OnStop_Implementation( FMobaAbilityRunContext context ) override;

private:
	UMobaAbility* PassiveAbility;
	UDesertClawAutoAttackAbilityData* CustomData;
};

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "Characters/DesertClaw/DesertClawPassiveAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"
#include "DesertClawAutoAttackAbility.generated.h"


/*
 *	Ability Data
 */
UCLASS()
class MOBARTFX_API UDesertClawAutoAttackAbilityData : public UMobaAbilityData
{
	GENERATED_BODY()

public:
	//  Passive sand cost per second
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float SandCost = 0.15f;

	//  Max range of auto-attack
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float Range = 750.0f;

	//  Damage per second
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float Damage = 50.0f;

	//  Radius of sphere trace
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	float Radius = 15.0f;

	//  Trace query type
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Auto-Attack" )
	TEnumAsByte<ETraceTypeQuery> TraceType;

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
	UDesertClawPassiveAbility* PassiveAbility;
	UDesertClawAutoAttackAbilityData* CustomData;
};

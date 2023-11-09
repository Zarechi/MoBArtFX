#pragma once

#include "CoreMinimal.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "Characters/DesertClaw/DesertClawUltimateDecal.h"
#include "Characters/DesertClaw/DesertClawUltimatePillar.h"
#include "Characters/DesertClaw/DesertClawPassiveAbility.h"
#include "DesertClawUltimateAbility.generated.h"

/*
 *	Ability Data
 */
UCLASS()
class MOBARTFX_API UDesertClawUltimateAbilityData : public UMobaAbilityData
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Placement" )
	float PlacementRange = 750.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Placement" )
	TEnumAsByte<ECollisionChannel> PlacementCollisionChannel;

	//  Maximum time to end the startup phase
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Placement" )
	float StartupTime = 6.0f;
	
	//  Delay after startup has ended to refill the passive
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float RefillDelay = 0.4f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarFallSpeed = 7500.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarStopTime = 5.0;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Decal" )
	float DecalRadius = 450.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Decal" )
	float DecalHeight = 50000.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Decal" )
	TSubclassOf<ADesertClawUltimateDecal> DecalActorClass;
};

/**
 * 
 */
UCLASS()
class MOBARTFX_API UDesertClawUltimateAbility : public UMobaAbility
{
	GENERATED_BODY()
	
public:
	void OnInitialize_Implementation() override;
	void OnTick_Implementation( float dt ) override;
	void OnRun_Implementation( FMobaAbilityRunContext context ) override;
	void OnStop_Implementation( FMobaAbilityRunContext context ) override;

	void TriggerPillar( int index );

private:
	void BeginStartup();
	void EndStartup();

	void RefillGaugeAfterDelay();
	void RefillGauge();

	void SpawnDecal();
	FVector GetDecalScaleFromSize( float radius, float height );

	void SpawnPillars();

	float StartupTime;

	TArray<ADesertClawUltimatePillar*> Pillars;

	ADesertClawUltimateDecal* UltimateActor;
	UDesertClawPassiveAbility* PassiveAbility;
	UDesertClawUltimateAbilityData* CustomData;
};

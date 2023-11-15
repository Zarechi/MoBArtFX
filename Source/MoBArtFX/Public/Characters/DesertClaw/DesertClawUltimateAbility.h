#pragma once

#include "CoreMinimal.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "Characters/DesertClaw/DesertClawUltimateDecal.h"
#include "Characters/DesertClaw/DesertClawUltimatePillar.h"
#include "Characters/DesertClaw/DesertClawPassiveAbility.h"
#include "LevelSequencePlayer.h"
#include "DesertClawUltimateAbility.generated.h"

/*
 *	Ability Data
 */
UCLASS()
class MOBARTFX_API UDesertClawUltimateAbilityData : public UMobaAbilityData
{
	GENERATED_BODY()

public:
	//  Delay after startup has ended to refill the passive
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float RefillDelay = 0.4f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Placement" )
	float PlacementRange = 750.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Placement" )
	TEnumAsByte<ECollisionChannel> PlacementCollisionChannel;

	//  Maximum time to end the startup phase
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Placement" )
	float StartupTime = 6.0f;

	//  Falling speed of pillar
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarFallSpeed = 7500.0f;

	//  Time in seconds a pillar will force turn un-active after its fall has begun
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarStopTime = 5.0f;

	//  Damage to apply when a pillar fall on an actor
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarDamage = 100.0f;

	/*
	 *  Location of pillars when not active. 
	 *  Since pillars collisions and visibility are disabled in this case, their location shouldn't have too much impact on the game. 
	 */
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	FVector PillarDefaultLocation { 0.0f, 0.0f, -5000.0f };

	//  Height of the pillar
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarHeight = 15.0f;

	//  When falling, the height offset a pillar should have from spawn
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	float PillarSpawnOffsetZ = 6000.0f;

	//  Custom spawn order of pillars as a list of pillar indices, it must contains the size of pillars
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	TArray<int> PillarSpawnOrder;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Pillar" )
	TSubclassOf<ADesertClawUltimatePillar> PillarActorClass;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Decal" )
	float DecalRadius = 450.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Decal" )
	float DecalHeight = 50000.0f;

	//  Time in seconds the decal hide after fall has ended (i.e. last pillar has been triggered)
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate's Decal" )
	float DecalHideTime = 2.0f;

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

	UFUNCTION( BlueprintCallable )
	void TriggerNextPillar();
	void TriggerPillar( int index );

	void BeginStartup();
	void EndStartup();

	void BeginFall();
	UFUNCTION( BlueprintCallable )
	void EndFall();

	ADesertClawUltimateDecal* GetDecalActor() { return DecalActor; }
	UDesertClawUltimateAbilityData* GetCustomData() { return CustomData; }

private:
	void RefillGaugeAfterDelay();
	void RefillGauge();

	void SpawnDecal();
	FVector GetDecalScaleFromSize( float radius, float height );

	void SpawnPillars();

	int CurrentPillarIndex = -1;
	float StartupTime;

	//  ultimate actors
	TArray<ADesertClawUltimatePillar*> Pillars;
	ADesertClawUltimateDecal* DecalActor;

	UDesertClawPassiveAbility* PassiveAbility;
	UDesertClawUltimateAbilityData* CustomData;
};

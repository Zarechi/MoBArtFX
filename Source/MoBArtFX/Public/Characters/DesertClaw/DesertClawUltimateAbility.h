#pragma once

#include "CoreMinimal.h"
#include "Characters/DesertClaw/MobaAbility.h"
#include "Characters/DesertClaw/DesertClawUltimateDecal.h"
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
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float PlacementRange = 750.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	TEnumAsByte<ECollisionChannel> PlacementCollisionChannel;

	//  Maximum time to end the startup phase
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float StartupTime = 6.0f;
	
	//  Delay after startup has ended to refill the passive
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float RefillDelay = 0.4f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float DecalRadius = 450.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
	float DecalHeight = 50000.0f;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Ultimate" )
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

private:
	void BeginStartup();
	void EndStartup();

	void RefillGaugeAfterDelay();
	void RefillGauge();

	void SpawnDecal();
	FVector GetDecalScaleFromSize( float radius, float height );

	float StartupTime;

	ADesertClawUltimateDecal* UltimateActor;
	UDesertClawPassiveAbility* PassiveAbility;
	UDesertClawUltimateAbilityData* CustomData;
};

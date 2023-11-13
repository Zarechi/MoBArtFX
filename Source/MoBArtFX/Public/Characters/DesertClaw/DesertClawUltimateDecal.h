#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "ActorSequenceComponent.h"
#include "DesertClawUltimateDecal.generated.h"

class UDesertClawUltimateAbility;

UCLASS()
class MOBARTFX_API ADesertClawUltimateDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADesertClawUltimateDecal();
	
	void SetupAbility( UDesertClawUltimateAbility* ability );

	UFUNCTION( BlueprintImplementableEvent, BlueprintPure )
	FVector GetSpawnLocation( int index );
	UFUNCTION( BlueprintCallable, BlueprintPure )
	int GetSpawnCount() { return SpawnCount; }

	UFUNCTION( BlueprintImplementableEvent, BlueprintPure )
	UActorSequenceComponent* GetSequenceComponent();

	UFUNCTION( BlueprintCallable, BlueprintPure )
	UDesertClawUltimateAbility* GetAbility() { return Ability; }

	UDecalComponent* GetDecalComponent() { return DecalComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

private:
	UPROPERTY( EditAnywhere )
	int SpawnCount = 0;

	UPROPERTY( EditAnywhere )
	UDecalComponent* DecalComponent;

	UDesertClawUltimateAbility* Ability;
};

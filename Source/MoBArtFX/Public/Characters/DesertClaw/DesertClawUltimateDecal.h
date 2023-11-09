#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "DesertClawUltimateDecal.generated.h"

UCLASS()
class MOBARTFX_API ADesertClawUltimateDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADesertClawUltimateDecal();

	UFUNCTION( BlueprintImplementableEvent, BlueprintPure )
	FVector GetSpawnLocation( int index );
	UFUNCTION( BlueprintCallable, BlueprintPure )
	int GetSpawnCount() { return SpawnCount; }

	UDecalComponent* GetDecalComponent() { return DecalComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

private:
	UPROPERTY( EditAnywhere )
	int SpawnCount = 0;

	UPROPERTY( EditAnywhere )
	UDecalComponent* DecalComponent;
};

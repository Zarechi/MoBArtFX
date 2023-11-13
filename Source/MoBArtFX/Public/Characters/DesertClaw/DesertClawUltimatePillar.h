#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawUltimatePillar.generated.h"

class UDesertClawUltimateAbility;
class UDesertClawUltimateAbilityData;

UCLASS()
class MOBARTFX_API ADesertClawUltimatePillar : public AActor
{
	GENERATED_BODY()

public:
	ADesertClawUltimatePillar();

	void SetupAbility( UDesertClawUltimateAbility* ability );

	void TriggerFall();
	void StopFall();

	bool GetFalling() const { return IsFalling; }

	UPROPERTY( EditAnywhere )
	UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

private:
	void OnMeshBeginOverlap( 
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	bool IsFalling = false;
	FTimerHandle StopTimerHandle;

	UDesertClawUltimateAbility* Ability;
	UDesertClawUltimateAbilityData* CustomData;
};

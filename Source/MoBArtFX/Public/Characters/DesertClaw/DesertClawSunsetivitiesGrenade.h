

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawSunsetivitiesGrenade.generated.h"

class ADesertClawSunsetivitiesShield;
class UDesertClawSunsetivitiesAbilityData;

UCLASS()
class MOBARTFX_API ADesertClawSunsetivitiesGrenade : public AActor
{
	GENERATED_BODY()

public:
	ADesertClawSunsetivitiesGrenade();

	void SetupData( UDesertClawSunsetivitiesAbilityData* data );

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

	UFUNCTION()
	void OnMeshHit(
		UPrimitiveComponent* HitComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit
	);

private:
	bool IsTriggered = false;
	float TriggerTime = 0.5f;

	FRotator SpawnRotation;

	UDesertClawSunsetivitiesAbilityData* CustomData;
};



#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawSunsetivitiesGrenade.generated.h"

UCLASS()
class MOBARTFX_API ADesertClawSunsetivitiesGrenade : public AActor
{
	GENERATED_BODY()

public:
	ADesertClawSunsetivitiesGrenade();

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

	void OnMeshOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

private:
	UPROPERTY( VisibleAnywhere )
	UStaticMeshComponent* Mesh;

};

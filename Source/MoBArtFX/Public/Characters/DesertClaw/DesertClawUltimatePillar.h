#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawUltimatePillar.generated.h"

class UDesertClawUltimateAbilityData;

UCLASS()
class MOBARTFX_API ADesertClawUltimatePillar : public AActor
{
	GENERATED_BODY()

public:
	ADesertClawUltimatePillar();

	void SetupData( UDesertClawUltimateAbilityData* data );

	void TriggerFall();
	void StopFall();

	bool GetFalling() const { return IsFalling; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

private:
	bool IsFalling = false;
	FTimerHandle StopTimerHandle;

	UDesertClawUltimateAbilityData* Data;
};

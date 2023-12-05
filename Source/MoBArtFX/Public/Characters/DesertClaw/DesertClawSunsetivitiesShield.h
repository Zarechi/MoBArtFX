#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawSunsetivitiesShield.generated.h"

UCLASS()
class MOBARTFX_API ADesertClawSunsetivitiesShield : public AActor
{
	GENERATED_BODY()
	
public:	
	ADesertClawSunsetivitiesShield();

	UFUNCTION( BlueprintCallable )
	void Activate( float time );
};

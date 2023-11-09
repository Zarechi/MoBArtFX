#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawUltimateManager.generated.h"

UCLASS()
class MOBARTFX_API ADesertClawUltimateManager : public AActor
{
	GENERATED_BODY()

public:
	ADesertClawUltimateManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

};

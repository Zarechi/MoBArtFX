#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_CainerMonstro.generated.h"


UCLASS()
class MOBARTFX_API AAIC_CainerMonstro : public AAIController
{
	GENERATED_BODY()

public:
	bool SetDestination(FVector destination);
	bool IsMoving();
	void Stop();

protected:
	void OnPossess(APawn* pawn) override;
};

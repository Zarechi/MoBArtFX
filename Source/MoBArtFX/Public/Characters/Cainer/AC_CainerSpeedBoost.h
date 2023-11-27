#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_CainerSpeedBoost.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBARTFX_API UAC_CainerSpeedBoost : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_CainerSpeedBoost();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void TriggerSpeedBoost(float speedBoost, float duration);

	float baseSpeed{ 0.0f };
	float boostTimer{ 0.0f };


private:
	void Boost(float boostValue);


protected:
	virtual void BeginPlay() override;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_CainerFlash.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOBARTFX_API UAC_CainerFlash : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_CainerFlash();


	UFUNCTION(BlueprintImplementableEvent)
	void Flash(float duration);


protected:
	virtual void BeginPlay() override;
};

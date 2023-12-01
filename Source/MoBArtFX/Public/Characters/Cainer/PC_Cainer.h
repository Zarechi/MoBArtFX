#pragma once

#include "CoreMinimal.h"
#include "PC_MoBArtFX.h"
#include "CainerCharacter.h"
#include "PC_Cainer.generated.h"


UCLASS() 
class MOBARTFX_API APC_Cainer : public APC_MoBArtFX 
{
	GENERATED_BODY()
	
public:
	void BindAbilitiesActions() override;


	/** InputActions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PingMonstroAction;


protected:
	/* InputEvents */
	void PingMonstro(const FInputActionValue& Value);
};

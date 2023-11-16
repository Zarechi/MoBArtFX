#pragma once

#include "CoreMinimal.h"
#include "PC_MoBArtFX.h"
#include "MobaAbility.h"
#include "DesertClawPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API ADesertClawPlayerController : public APC_MoBArtFX
{
	GENERATED_BODY()
	
public:
	void BindAbilitiesActions() override;

	void BindAbility( UMobaAbility* ability );

private:
	ADesertClawCharacter* Character;
};

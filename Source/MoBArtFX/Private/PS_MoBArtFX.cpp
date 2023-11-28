#include "PS_MoBArtFX.h"
#include "HUD_MoBArtFX.h"

void APS_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	PlayerDatas = PlayerDatas_Asset.LoadSynchronous();

	if(PlayerDatas)
	{
		PlayerDatas->CurrentHealth = PlayerDatas->MaxHealth;
		PlayerDatas->CurrentAmmo = PlayerDatas->MaxAmmo;
	}
}

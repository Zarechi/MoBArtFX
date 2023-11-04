// Fill out your copyright notice in the Description page of Project Settings.


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

		//Cast<AHUD_MoBArtFX>(GetPlayerController()->GetHUD())->ConstructViewport(PlayerDatas->ViewportClass);
	}
	else
	{
		if(PlayerDatas_Asset)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerDatas not valid with : %s"), *PlayerDatas_Asset.GetAssetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerDatas_Asset is not valid"));
		}
	}
}

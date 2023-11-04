// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_MoBArtFX.h"

void APS_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	PlayerDatas->CurrentHealth = PlayerDatas->MaxHealth;
	PlayerDatas->CurrentAmmo = PlayerDatas->MaxAmmo;
}

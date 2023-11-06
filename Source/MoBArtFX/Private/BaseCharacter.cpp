// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Engine/DamageEvents.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

UPlayerInfos* ABaseCharacter::GetPlayerDatas()
{
	if (GetPlayerState<APlayerState>())
	{
		return GetPlayerState<APS_MoBArtFX>()->PlayerDatas;
	}
	else
	{
		if(DebugPlayerInfos)
			return DebugPlayerInfos;
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find PlayerDatas"));

	return nullptr;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::AutoAttack_Implementation()
{	
	if(GetPlayerDatas()->CurrentAmmo <= 0)
	{
		GetPlayerDatas()->CurrentAmmo = 0;
		Reload();
	}
}

void ABaseCharacter::Reload_Implementation()
{
	GetPlayerDatas()->CurrentAmmo = GetPlayerDatas()->MaxAmmo;
}

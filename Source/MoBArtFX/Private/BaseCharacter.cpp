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
		UE_LOG(LogTemp, Warning, TEXT("PlayerState's Datas"));
		return GetPlayerState<APS_MoBArtFX>()->PlayerDatas;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Debug's Datas"))
		return DebugPlayerInfos;
	}

	UE_LOG(LogTemp, Error, TEXT("PlayerState not valid"));

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

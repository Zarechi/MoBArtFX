// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Cainer/CainerMonstro.h"

// Sets default values
ACainerMonstro::ACainerMonstro()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACainerMonstro::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACainerMonstro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACainerMonstro::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/PC_MoBArtFX_King.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <EnhancedInputSubsystems.h>

void APC_MoBArtFX_King::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterK = Cast<ABaseCharacter_King>(UGameplayStatics::GetPlayerCharacter(this, 0));

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(Spell01_Action, ETriggerEvent::Triggered, this, &APC_MoBArtFX_King::Spell01);
		EnhancedInputComponent->BindAction(Spell01_Action, ETriggerEvent::Completed, this, &APC_MoBArtFX_King::Spell01End);
	}
}

void APC_MoBArtFX_King::Spell01(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_01"));
	PlayerCharacterK->Spell_01_Implementation();
}

void APC_MoBArtFX_King::Spell01End(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("End Spell_01"));
	PlayerCharacterK->Spell_01End();
}

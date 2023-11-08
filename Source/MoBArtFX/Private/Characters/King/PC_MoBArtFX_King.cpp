// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/PC_MoBArtFX_King.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <EnhancedInputSubsystems.h>

void APC_MoBArtFX_King::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Spell01_Action, ETriggerEvent::Completed, this, &APC_MoBArtFX_King::Spell01End);
	}
}

void APC_MoBArtFX_King::Spell01End(const FInputActionValue& Value)
{
	TObjectPtr<ABaseCharacter_King> PlayerCharacterK = Cast<ABaseCharacter_King>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_01"));
	PlayerCharacterK->Spell_01End();
}

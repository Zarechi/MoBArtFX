// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/PC_MoBArtFX_King.h"
#include <EnhancedInputComponent.h>

void APC_MoBArtFX_King::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Spell01_EndAction, ETriggerEvent::Completed, this, &APC_MoBArtFX_King::Spell01End);
	}
}

void APC_MoBArtFX_King::Spell01End(const FInputActionValue& Value)
{

}

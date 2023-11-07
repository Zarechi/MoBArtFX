// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/PC_MoBArtFX_King.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <EnhancedInputSubsystems.h>

void APC_MoBArtFX_King::BeginPlay()
{
	/*Super::BeginPlay();

	PlayerCharacter = Cast<ABaseCharacter_King>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Spell01_EndAction, ETriggerEvent::Completed, this, &APC_MoBArtFX_King::Spell01End);
	}*/

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

	PlayerCharacter = Cast<ABaseCharacter_King>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_DefaultPlayer, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APC_MoBArtFX::StopJump);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Look);

		//Attacks
		EnhancedInputComponent->BindAction(AutoAttackAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::AutoAttack);
		EnhancedInputComponent->BindAction(Spell01_Action, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Spell01);
		EnhancedInputComponent->BindAction(Spell02_Action, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Spell02);
		EnhancedInputComponent->BindAction(UltimateAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Ultimate);
	}
}

void APC_MoBArtFX_King::Spell01End(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_01"));
}

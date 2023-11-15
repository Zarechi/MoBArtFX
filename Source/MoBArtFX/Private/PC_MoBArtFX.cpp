// Fill out your copyright notice in the Description page of Project Settings.

#include "PC_MoBArtFX.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUD_MoBArtFX.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "HUD_MoBArtFX.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void APC_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	
	PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
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
		EnhancedInputComponent->BindAction(AutoAttackAction, ETriggerEvent::Completed, this, &APC_MoBArtFX::AutoAttack);
		EnhancedInputComponent->BindAction(Spell01_Action, ETriggerEvent::Completed, this, &APC_MoBArtFX::Spell01);
		EnhancedInputComponent->BindAction(Spell02_Action, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Spell02);
		EnhancedInputComponent->BindAction(UltimateAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Ultimate);
	}
	
	
}

void APC_MoBArtFX::Move(const FInputActionValue& Value)
{
	// Forward Movement
	PlayerCharacter->AddMovementInput(UKismetMathLibrary::GetForwardVector(GetControlRotation()), Value.Get<FVector2D>().X);
	
	// Right Movement
	PlayerCharacter->AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotation()), Value.Get<FVector2D>().Y);
}

void APC_MoBArtFX::Look(const FInputActionValue& Value)
{
	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(Value.Get<FVector2D>().Y * -1);
}

void APC_MoBArtFX::Jump(const FInputActionValue& Value)
{
	PlayerCharacter->Jump();
}

void APC_MoBArtFX::StopJump(const FInputActionValue& Value)
{
	PlayerCharacter->StopJumping();
}

void APC_MoBArtFX::AutoAttack(const FInputActionValue& Value)
{
	PlayerCharacter->AutoAttack();
}

void APC_MoBArtFX::Spell01(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_01"));
	PlayerCharacter->Spell_01();
}

void APC_MoBArtFX::Spell02(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_02"));
	PlayerCharacter->Spell_02();
}

void APC_MoBArtFX::Ultimate(const FInputActionValue& Value)
{
	PlayerCharacter->Ultimate();
}

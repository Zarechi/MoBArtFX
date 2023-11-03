// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "BaseCharacter.h"
#include "PC_MoBArtFX.generated.h"

class UInputComponent;
class UInputMappingContext;

UCLASS()
class MOBARTFX_API APC_MoBArtFX : public APlayerController
{
	GENERATED_BODY()

	/* FUNCTIONS */
public:
	virtual void BeginPlay() override;
	
protected:
	/** InputEvents */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void AutoAttack(const FInputActionValue& Value);
	void Spell01(const FInputActionValue& Value);
	void Spell02(const FInputActionValue& Value);
	void Ultimate(const FInputActionValue& Value);
	
private:
	
	/* VARIABLES */
public:
	UPROPERTY(BlueprintReadOnly, Category=Character)
	ABaseCharacter* PlayerCharacter = nullptr;
	
	/* MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_DefaultPlayer;

	/** InputActions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AutoAttackAction;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Spell01_Action;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Spell02_Action;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UltimateAction;
	
protected:
private:
};

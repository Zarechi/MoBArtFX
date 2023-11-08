// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.h"
#include "Potion.h"
#include "PoisonPotion.h"
#include "Cauldron.h"
#include "Vivianne.generated.h"

UCLASS()
class MOBARTFX_API AVivianne : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVivianne();

protected:

	// Potion related
	float healCooldown = 0.f;
	float poisonCooldown = 0.f;
	bool healThrowable = true;
	bool poisonThrowable = true;

	// Sprint related
	float sprintCooldown = 0.f;
	float sprintDuration = 0.f;
	bool sprinting = false;
	bool sprintReady = true;

	//ultimate related
	float ultimateCooldown = 0.f;
	bool ultimateReady = true;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere);
	TSubclassOf<APotion> potionClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<APoisonPotion> poisonPotionClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<ACauldron> cauldronClass;

	// Called every frame
	void Tick(float DeltaTime) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Potion attacks
	void Potion(const FInputActionValue& Value, bool healing);

	// Sprint
	void Sprint(const FInputActionValue& value);

	// RayCast attack
	void Spell(const FInputActionValue& value);

	// Ultimate
	void Ultimate(const FInputActionValue& value);



};

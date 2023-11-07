// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseCharacter_King.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API ABaseCharacter_King : public ABaseCharacter
{
	GENERATED_BODY()

	/*FUNCTIONS*/
public:
	// Sets default values for this character's properties
	ABaseCharacter_King();

	virtual void Death_Implementation() override {};

	// Attacks
	virtual void AutoAttack_Implementation() override;
	virtual void Spell_01_Implementation() override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_01End();
	virtual void Spell_01End_Implementation();
	virtual void Spell_02_Implementation() override;
	virtual void Ultimate_Implementation() override;


	virtual void Reload_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	
};

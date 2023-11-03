// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MOBARTFX_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*VARIABLE*/
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Health")
	int CurrentHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Health")
	int MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Ammo")
	int MaxAmmo = 10;
	UPROPERTY(BlueprintReadWrite, Category="MoBA_Character|Stats|Ammo")
	int CurrentAmmo = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Cooldowns")
	float CD_AutoAttack = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Cooldowns")
	float CD_Spell01 = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Cooldowns")
	float CD_Spell02 = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoBA_Character|Stats|Cooldowns")
	float CD_Ultimate = 10.f;

protected:
	
private:
	
	/*FUNCTIONS*/
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Attacks
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AutoAttack();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_01();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_02();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Ultimate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Death();
private:
};

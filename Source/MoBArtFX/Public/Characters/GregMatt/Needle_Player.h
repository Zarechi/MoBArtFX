// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "E_AttackType.h"
#include "Needle_Player.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API ANeedle_Player : public ABaseCharacter
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	void Spell_01_Implementation() override;
	void Spell_02_Implementation() override;
	void Ultimate_Implementation() override;

	void AutoAttack_Implementation() override;
	void Reload_Implementation() override;

	//void Death_Implementation() override;

	void ShootProjectile(int attType);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	bool IsAI = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchTypeInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 1000.0f;

	float CurrentHealth = 0;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float StunDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float SlownessDelay = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float SlownessForce = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	float DodgeImpulsionDelay = 0.25f;

	float dodgeCurrentCooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	TArray <TEnumAsByte<AttackType>> needleStack;

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//void UpdateAIHealth(float health);


	///////////////////////////////////////////////////////////////////// ATTACK

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float NeedleBaseDamage = 47;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	int MaxStack = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float DamageIncreasePerStack = 1.5f;

	UFUNCTION(BlueprintCallable)
	void SwitchAttackType();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float BasicAttackCooldown = 1.f / 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float SkillShotCooldown = 1;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float DodgeSkillShootCooldown = 1;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float TeleportCooldown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float UltimateCooldown = 1;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UClass* ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "false"))
	float BasicAttackCurrentCooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "false"))
	float SkillShotCurrentCooldown = 0;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "false"))
	float DodgeSkillShootCurrentCooldown = 0;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "false"))
	float TeleportCurrentCooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "false"))
	float UltimateCurrentCooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<AttackType> CurrentAttackType;

	protected:
		virtual void BeginPlay();
		virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
};

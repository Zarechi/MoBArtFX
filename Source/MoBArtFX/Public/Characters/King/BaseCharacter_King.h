// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseCharacter_King.generated.h"

class UCameraComponent;
class UStaticMeshComponent;
class UArrowComponent;

/**
 * 
 */
UCLASS()
class MOBARTFX_API ABaseCharacter_King : public ABaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshGodHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> UltimateLHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> UltimateRHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> SpellSpawnPoint;

	/*FUNCTIONS*/
public:
	// Sets default values for this character's properties
	ABaseCharacter_King();
	virtual void Tick(float DeltaTime) override;

	void AutoAttack_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Spell_01End();

	void Spell_01_Implementation() override;
	void Spell_02_Implementation() override;
	void Ultimate_Implementation() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	// ====================
	// Default Value
	// ====================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float DefaultGravityScale = 1.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float DefaultMaxWalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float AbilityMaxWalkSpeed = 280.0f;

	// ====================
	// Auto Attack
	// ====================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AutoAttack, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UClass> ProjectilClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AutoAttack, meta = (AllowPrivateAccess = "true"))
	float AttackRate = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AutoAttack, meta = (AllowPrivateAccess = "true"))
	FRotator Calibrate = FRotator(2.0f, 0.0f, 0.0f);

	float timerDefaultAttack = 0.f;

	// ====================
	// Spell_01
	// ====================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability1, meta = (AllowPrivateAccess = "true"))
	float AbilityHealth = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability1, meta = (AllowPrivateAccess = "true"))
	float cooldownAbilityBreak = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability1, meta = (AllowPrivateAccess = "true"))
	float abilityActivationTime = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability1, meta = (AllowPrivateAccess = "true"))
	float abilityRetractationTime = .3f;

	bool Spell01IsActive = false;
	bool godHandBreak = false;
	float timerGodHandBreack = 0.f;
	float currentGodHandHealth;

	void EndGodHand();

	// ====================
	// Spell_02
	// ====================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability2, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UClass> ActorAbility2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability2, meta = (AllowPrivateAccess = "true"))
	float ability2ActivationTime = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability2, meta = (AllowPrivateAccess = "true"))
	float cooldownAbility2 = 8.f;

	bool Spell02IsActive = false;
	float timerIronShears = 0.f;

	// ====================
	// Ultimate
	// ====================
	bool UltiIsActive = false;
};

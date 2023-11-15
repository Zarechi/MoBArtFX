#pragma once
#include "CoreMinimal.h"
#include "../../BaseCharacter.h"
#include "CharacterCrow.generated.h"

UCLASS()
class MOBARTFX_API ACharacterCrow : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ACharacterCrow();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Abilities

	void AutoAttack_Implementation() override;
	void Spell_01_Implementation() override;
	void Spell_02_Implementation() override;
	void Ultimate_Implementation() override;

	// Cooldown
	float LastUsedTime;
	float RemainingCooldown;
	float CastingTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float CooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Settings")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Settings")
	float ProjectileSpeed;

	// Class of the sphere projectile
	TSubclassOf<class AMOBA_Projectile> ProjectileClass;

protected:

	virtual void BeginPlay() override;

};

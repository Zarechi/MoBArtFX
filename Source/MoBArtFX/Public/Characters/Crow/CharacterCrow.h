#pragma once
#include "CoreMinimal.h"
#include "../../BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
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
	float LastUsedAATime;
	float LastUsedSpell01Time;
	float RemainingCooldown;
	float CastingTime;
	float AngleBetweenProjectiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float AACD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float AADamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float ProjectileLifetime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Redemption Feather Setting")
	float RedemptionFeatherCD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Redemption Feather Setting")
	float RedemptionFeatherDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Redemption Feather Setting")
	float RedemptionFeatherRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Redemption Feather Setting")
	float RedemptionFeatherKB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Redemption Feather Setting")
	float DistanceFromChara;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Redemption Feather Setting")
	bool bRecoilApplied;


	// Class of the sphere projectile
	TSubclassOf<class AMOBA_Projectile> ProjectileClass;

	// Class Capsule
	//UCapsuleComponent* CapsuleComponent;

protected:

	virtual void BeginPlay() override;
	int32 SideCounter = 0; // Initialize SideCounter to 0

};

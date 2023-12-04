#pragma once
#include "CoreMinimal.h"
#include "../../BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <Components/SplineComponent.h>
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

	bool CanUseGlideAbility() const;
	//void ShowFlashbangEffect();
	//void HideFlashbangEffect();
	void DestroyFlashbangWidget();
	void UpdateGlide();

	// Cooldown
	float LastUsedAATime;
	float LastUsedSpell01Time;
	float LastUsedSpell02Time;
	float LastUsedUltimateTime;
	float CastingTime;
	float AngleBetweenProjectiles;

	// Redemption Feather
	bool bRecoilApplied;

	// Scarecrow Breeze
	bool bIsGliding;
	bool bIsFlashing;
	float GlideStartTime;

	// AUTO ATTACK 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float AACD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float AADamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Auto Attack Setting")
	float ProjectileLifetime;

	// REDEMPTION FEATHER

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

	// SCARECROW BREEZE

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float ScarecrowBreezeCD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float GlideDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float JumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float GlideAirControl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float DefaultAirControl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float DefaultGravity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	bool bInfiniteGlideDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scarecrow Breeze Settings")
	float FlashbangDuration;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UUserWidget> HUDFlashEffect;

	UPROPERTY()
	UUserWidget* FlashbangWidget;

	// ULTIMATE VENFEGUL RAVEN
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vengeful Raven Settings")
	float VengefulRavenCD;

	// Class of the sphere projectile
	TSubclassOf<class ACrow_Projectile> ProjectileClass;

protected:

	virtual void BeginPlay() override;
	int32 SideCounter = 0; // Initialize SideCounter to 0

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USplineComponent* CurvedMovementSpline;

};

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PS_MoBArtFX.h"
#include "BaseCharacter.generated.h"

class APC_MoBArtFX;

UCLASS()
class MOBARTFX_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	float TakeDamage(
		const float Damage, 
		FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser
	) override;

	/*
	 *  Intermediate function called before TakeDamage to mitigate damage taken
	 * 
	 *  Returns amount of damage to apply
	 */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	float MitigateDamage( float damage, AActor* causer );

	UFUNCTION( BlueprintCallable )
	void ApplySpellCooldown( float time, EMobaAbilitySlot type );
	UFUNCTION( BlueprintCallable, BlueprintPure )
	bool IsSpellOnCooldown( EMobaAbilitySlot type ) const;
	UFUNCTION( BlueprintCallable, BlueprintPure )
	float GetSpellCooldown( EMobaAbilitySlot type ) const;

	// Attacks
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void AutoAttack();
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void Reload();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void Spell_01();
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void Spell_02();
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void Ultimate();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void Death();

	// PlayerDatas
	void SetPlayerDatas( UPlayerInfos* data );
	UFUNCTION( BlueprintCallable, BlueprintPure )
	UPlayerInfos* GetPlayerDatas();

	UFUNCTION( BlueprintCallable, BlueprintPure )
	APS_MoBArtFX* GetCustomPlayerState() const { return CustomPlayerState; }
	UFUNCTION( BlueprintCallable, BlueprintPure )
	APC_MoBArtFX* GetCustomPlayerController() const { return CustomPlayerController; }

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSoftClassPtr<UPlayerInfos> DebugPlayerInfosAsset;
	UPROPERTY( BlueprintReadWrite )
	TObjectPtr<UPlayerInfos> DebugPlayerInfos;

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	virtual void SetupData( UPlayerInfos* data );

	TMap<EMobaAbilitySlot, float> SpellTimers;

	TObjectPtr<APS_MoBArtFX> CustomPlayerState;
	TObjectPtr<APC_MoBArtFX> CustomPlayerController;
};

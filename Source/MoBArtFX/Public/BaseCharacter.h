#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PS_MoBArtFX.h"
#include "BaseCharacter.generated.h"

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

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSoftClassPtr<UPlayerInfos> DebugPlayerInfosAsset;
	UPROPERTY( BlueprintReadWrite )
	TObjectPtr<UPlayerInfos> DebugPlayerInfos;

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	virtual void SetupData( UPlayerInfos* data );

	TObjectPtr<APS_MoBArtFX> PlayerState;
};

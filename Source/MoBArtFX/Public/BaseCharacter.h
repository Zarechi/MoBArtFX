// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	UFUNCTION( BlueprintCallable, BlueprintPure )
	UPlayerInfos* GetPlayerDatas();

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSoftClassPtr<UPlayerInfos> DebugPlayerInfosAsset;
	UPROPERTY( BlueprintReadWrite )
	TObjectPtr<UPlayerInfos> DebugPlayerInfos;

protected:
	virtual void BeginPlay() override;
	//float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};

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

	/*VARIABLE*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UPlayerInfos> DebugPlayerInfosAsset;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UPlayerInfos> DebugPlayerInfos;
protected:	
private:
	
	/*FUNCTIONS*/
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Death();
	virtual void Death_Implementation() {};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Attacks
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AutoAttack();
	virtual void AutoAttack_Implementation();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_01();
	virtual void Spell_01_Implementation() {}
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_02();
	virtual void Spell_02_Implementation() {}
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Ultimate();
	virtual void Ultimate_Implementation() {}

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();
	virtual void Reload_Implementation();

	// PlayerDatas
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayerInfos* GetPlayerDatas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:
};

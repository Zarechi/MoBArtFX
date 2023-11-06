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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Attacks
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AutoAttack();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_01();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Spell_02();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Ultimate();

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload();

	// PlayerDatas
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPlayerInfos* GetPlayerDatas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//float TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:
};

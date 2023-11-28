// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfos.h"
#include "CainerMonstro.h"
#include "CainerInfos.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API UCainerInfos : public UPlayerInfos
{
	GENERATED_BODY()

	/* VARIABLES */
public:
	/** Spells parameters */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Primary", meta = (min = 0.0f))
	float speedBoostValue = 1.5f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Primary", meta = (min = 0.0f))
	float speedBoostRadius = 1000.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Primary", meta = (min = 0.0f))
	float speedBoostDuration = 10.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary", meta = (min = 0.0f))
	float monstroLife = 2000.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary", meta = (min = 0.0f))
	float monstroMoveSpeed = 600.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary", meta = (min = 0.0f))
	float monstroPingMaxDist = 1500.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary")
	TSubclassOf<ACainerMonstro> monstroBlueprint;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Secondary")
	TObjectPtr<UParticleSystem> monstroPingParticles;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Ultimate", meta = (min = 0.0f))
	float flashRange = 3000.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|Ultimate", meta = (min = 0.0f))
	float flashDuration = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spells|AutoAttack", meta = (min = 0.0f))
	float autoattack_damage = 1.0f;
};

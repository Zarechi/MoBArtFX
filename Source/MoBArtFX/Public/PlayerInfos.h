// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInfos.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MOBARTFX_API UPlayerInfos : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="CrossHair")
	TObjectPtr<UMaterialInstance> CrossHairMat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="CrossHair")
	FVector2D CrossHairScale;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ammo")
	int32 MaxAmmo;
	UPROPERTY(BlueprintReadWrite, Category="Ammo", meta=(EditCondition=false))
	int32 CurrentAmmo;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Character")
	TObjectPtr<UMaterialInstance> CharacterMat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Character|Health")
	int32 MaxHealth;
	UPROPERTY(BlueprintReadWrite, Category="Character|Health", meta=(EditCondition=false))
	int32 CurrentHealth;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Primary")
	TObjectPtr<UMaterialInstance> Spell01_Mat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Primary")
	double Spell01_MaxCD;
	UPROPERTY(BlueprintReadWrite, Category="Spells|Primary", meta=(EditCondition=false))
	double Spell01_CurrentCD;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Secondary")
	TObjectPtr<UMaterialInstance> Spell02_Mat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Secondary")
	double Spell02_MaxCD;
	UPROPERTY(BlueprintReadWrite, Category="Spells|Secondary", meta=(EditCondition=false))
	double Spell02_CurrentCD;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Ultimate")
	TObjectPtr<UMaterialInstance> Ultimate_Mat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Ultimate")
	double Ultimate_MaxCD;
	UPROPERTY(BlueprintReadWrite, Category="Spells|Ultimate", meta=(EditCondition=false))
	double Ultimate_CurrentCD;

protected:
private:
};

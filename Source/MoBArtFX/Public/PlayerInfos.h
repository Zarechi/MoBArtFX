#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInfos.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MOBARTFX_API UPlayerInfos : public UDataAsset
{
	GENERATED_BODY()

	/* VARIABLES */
public:

	/** Crosshair parameters */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="CrossHair")
	TObjectPtr<UMaterialInstance> CrossHairMat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="CrossHair")
	FVector2D CrossHairScale = FVector2D(1.f, 1.f);

	/** Ammo parameters */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ammo")
	int32 MaxAmmo = 100;
	UPROPERTY(BlueprintReadWrite, Category="Ammo", meta=(EditCondition=false))
	int32 CurrentAmmo;

	/** Character parameters */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Character" )
	FString Name = "N/A";
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Character")
	TObjectPtr<UMaterialInstance> CharacterMat;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Character|Movement")
	float MaxWalkSpeed = 600.0f;
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Character|Movement" )
	float JumpVelocity = 420.0f;
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Character|Movement" )
	float AirControl = 0.05f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Character|Health")
	float MaxHealth = 1500;
	UPROPERTY(BlueprintReadWrite, Category="Character|Health", meta=(EditCondition=false))
	float CurrentHealth;

	/** Spells parameters */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|AutoAttack")
	double AutoAttack_CD = 0.7f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Primary")
	TObjectPtr<UMaterialInstance> Spell01_Mat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Primary")
	double Spell01_CD = 5.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Secondary")
	TObjectPtr<UMaterialInstance> Spell02_Mat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Secondary")
	double Spell02_CD = 15.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Ultimate")
	TObjectPtr<UMaterialInstance> Ultimate_Mat;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spells|Ultimate")
	double Ultimate_CD = 30.f;

	/* HUD Parameters */
	UPROPERTY(EditDefaultsOnly, Category = "Viewport")
	TSubclassOf<UUserWidget> ViewportClass;

protected:
private:
	
	/* FUNCTION */
public:
protected:
private:
};

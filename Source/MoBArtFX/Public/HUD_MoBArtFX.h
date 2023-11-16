// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "HUD_MoBArtFX.generated.h"

UENUM( BlueprintType )
enum class EMobaSpellType : uint8
{
	First        UMETA( DisplayName = "First" ),
	Second       UMETA( DisplayName = "Second" ),
	Ultimate     UMETA( DisplayName = "Ultimate" ),
};

/** HUD Interface */

UINTERFACE(MinimalAPI, Blueprintable)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};
class IHUDInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "HUD" )
	void Cooldown( double time, int type );
};

/** HUD Class */
UCLASS()
class MOBARTFX_API AHUD_MoBArtFX : public AHUD
{
	GENERATED_BODY()
	
	/* FUNCTIONS */
public:
	virtual void BeginPlay() override;

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "HUD" )
	void Cooldown( float time, EMobaSpellType type );
	
protected:
private:

	/* VARIABLES */
public:
	//TSubclassOf<UUserWidget> ViewportClass;
	
	UPROPERTY(BlueprintReadOnly, Category = Viewport)
	TObjectPtr<UUserWidget> ViewportInstance;
	
protected:
private:
};

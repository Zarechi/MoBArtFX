// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "HUD_MoBArtFX.generated.h"

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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void Cooldown(double _CooldownTime, int SpellNum);
};

/** HUD Class */

UCLASS()
class MOBARTFX_API AHUD_MoBArtFX : public AHUD
{
	GENERATED_BODY()
	
	/* FUNCTIONS */
public:
	virtual void BeginPlay() override;
	
protected:
private:

	/* VARIABLES */
public:
	//TSubclassOf<UUserWidget> ViewportClass;
	
	UPROPERTY(BlueprintReadOnly, Category = Viewport)
	UUserWidget* ViewportInstance;
	
protected:
private:
};

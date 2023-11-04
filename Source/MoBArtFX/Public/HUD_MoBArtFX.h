// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "HUD_MoBArtFX.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API AHUD_MoBArtFX : public AHUD
{
	GENERATED_BODY()
	
	/* FUNCTIONS */
public:
	void ConstructViewport(TSubclassOf<UUserWidget> _ViewportClass);
	
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

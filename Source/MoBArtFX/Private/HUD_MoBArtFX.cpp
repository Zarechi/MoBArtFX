// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_MoBArtFX.h"

#include "PS_MoBArtFX.h"
#include "Blueprint/UserWidget.h"

void AHUD_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UUserWidget> const ViewportClass = Cast<APS_MoBArtFX>(GetOwningPlayerController()->PlayerState)->PlayerDatas->ViewportClass;
	
	ViewportInstance = CreateWidget<>(GetOwningPlayerController(), ViewportClass, FName("Viewport"));
	ViewportInstance->AddToPlayerScreen();	
}

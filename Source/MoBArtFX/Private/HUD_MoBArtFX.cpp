// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_MoBArtFX.h"

#include "Blueprint/UserWidget.h"

void AHUD_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	ViewportInstance = CreateWidget<UUserWidget>(GetOwningPlayerController(), ViewportClass, FName("Viewport"));
	ViewportInstance->AddToPlayerScreen();	
}

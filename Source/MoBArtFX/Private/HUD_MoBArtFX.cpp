// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_MoBArtFX.h"

#include "Blueprint/UserWidget.h"

void AHUD_MoBArtFX::ConstructViewport(TSubclassOf<UUserWidget> _ViewportClass)
{
	ViewportInstance = CreateWidget<UUserWidget>(GetOwningPlayerController(), _ViewportClass, FName("Viewport"));
	ViewportInstance->AddToPlayerScreen();	
}

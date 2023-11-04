// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <PlayerInfos.h>
#include "PS_MoBArtFX.generated.h"

UCLASS()
class MOBARTFX_API APS_MoBArtFX : public APlayerState
{
	GENERATED_BODY()

	/* FUNCTIONS */
public:	
protected:
private:

	/* VARIABLES */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PlayerDatas")
	UPlayerInfos* PlayerDatas;
	
protected:
private:
};

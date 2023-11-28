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
	virtual void BeginPlay() override;
	
protected:
private:

	/* VARIABLES */
public:
	UPROPERTY(EditAnywhere, Category="PlayerDatas", meta=(AllowedClasses="UPlayerInfos"))
	TSoftObjectPtr<UPlayerInfos> PlayerDatas_Asset;
	UPROPERTY(BlueprintReadOnly, Category="PlayerDatas", meta=(EditCondition="false"))
	TObjectPtr<UPlayerInfos> PlayerDatas;
	
protected:
private:
};

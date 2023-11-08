// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PC_MoBArtFX.h"
#include <Characters/King/BaseCharacter_King.h>
#include "PC_MoBArtFX_King.generated.h"

/**
 * 
 */
UCLASS()
class MOBARTFX_API APC_MoBArtFX_King : public APC_MoBArtFX
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	void Spell01End(const FInputActionValue& Value);
};

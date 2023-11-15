// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Int_Interaction_Chara.h"
#include "AC_SlowDown.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBARTFX_API UAC_SlowDown : public UActorComponent, public IInt_Interaction_Chara
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_SlowDown();

	void SlowDownWalkSpeed();

	UFUNCTION(BlueprintNativeEvent, Category = "Interact")
	void SlowDown();
	virtual void SlowDown_Implementation() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float defaultWalkSpeed = .0f;
	float walkSpeedInSlowDown = .0f;

	TObjectPtr<ACharacter> chara = nullptr;

	/*
	* Percentage of speed reduce.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float percentSlowDown = 0.3f;

	/*
	* Slowdown duration.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float slowDownDuration = 1.f;
		
};

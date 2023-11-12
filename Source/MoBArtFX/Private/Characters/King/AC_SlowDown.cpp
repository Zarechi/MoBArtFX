// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/AC_SlowDown.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UAC_SlowDown::UAC_SlowDown()
{
	
}

void UAC_SlowDown::SlowDownWalkSpeed()
{
	chara->GetCharacterMovement()->MaxWalkSpeed = walkSpeedInSlowDown;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Slow"));

	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
		{
			chara->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed;
		}
	);

	
	FTimerHandle TimerH;
	GetWorld()->GetTimerManager().SetTimer(TimerH, Delegate, slowDownDuration, false);
}


// Called when the game starts
void UAC_SlowDown::BeginPlay()
{
	Super::BeginPlay();

	chara = Cast<ACharacter>(GetOwner());
	if (chara != nullptr)
	{
		defaultWalkSpeed = chara->GetCharacterMovement()->MaxWalkSpeed;
		walkSpeedInSlowDown = (1 - percentSlowDown) * defaultWalkSpeed;
	}
	
}


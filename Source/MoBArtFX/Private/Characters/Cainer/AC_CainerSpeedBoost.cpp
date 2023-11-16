#include "Characters/Cainer/AC_CainerSpeedBoost.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UAC_CainerSpeedBoost::UAC_CainerSpeedBoost()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAC_CainerSpeedBoost::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* owner = Cast<ACharacter>(GetOwner());
	if (owner->IsValidLowLevel())
	{
		baseSpeed = owner->GetCharacterMovement()->MaxWalkSpeed;
	}
}


void UAC_CainerSpeedBoost::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (boostTimer <= 0.0f) return;
	boostTimer -= DeltaTime;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::White, "Current speed boost : " + FString::SanitizeFloat(boostTimer) + " seconds remaining.");

	if (boostTimer <= 0.0f)
	{
		Boost(1.0f);
	}
}


void UAC_CainerSpeedBoost::TriggerSpeedBoost(float speedBoost, float duration)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Green, "Triggered speed boost of " + FString::SanitizeFloat(speedBoost) + " for " + FString::SanitizeFloat(duration) + " seconds on actor " + GetOwner()->GetName() + ".");

	boostTimer = duration;
	Boost(speedBoost);
}

void UAC_CainerSpeedBoost::Boost(float boostValue)
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	if (owner->IsValidLowLevel())
	{
		owner->GetCharacterMovement()->MaxWalkSpeed = baseSpeed * boostValue;
	}
}

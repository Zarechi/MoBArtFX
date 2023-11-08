// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Vivianne/Vivianne.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVivianne::AVivianne()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AVivianne::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVivianne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (sprintCooldown > 0)
	{
		sprintCooldown -= DeltaTime;
	}
	else if (sprintCooldown < 0 && !sprintReady)
	{
		sprintReady = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sprint ready"));
	}

	if (sprintDuration > 0)
	{
		sprintDuration -= DeltaTime;
	}
	else if (sprintDuration < 0 && sprinting)
	{
		sprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sprint off"));
	}

	if (healCooldown > 0)
	{
		healCooldown -= DeltaTime;
	}
	else if (healCooldown < 0 && !healThrowable)
	{
		healThrowable = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("heal ready"));

	}

	if (poisonCooldown > 0)
	{
		poisonCooldown -= DeltaTime;
	}
	else if (poisonCooldown < 0 && !poisonThrowable)
	{
		poisonThrowable = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("poison ready"));

	}

	if (ultimateCooldown > 0)
	{
		ultimateCooldown -= DeltaTime;
	}
	else if (ultimateCooldown < 0 && !ultimateReady)
	{
		ultimateReady = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ultimate ready"));

	}

}


void AVivianne::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AVivianne::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AVivianne::Potion(const FInputActionValue& Value, bool healing)
{
	APlayerCameraManager* playerCamera = GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->PlayerCameraManager : nullptr;


	FVector viewDirection = playerCamera->GetActorForwardVector();
	float distanceInFront = 50.0f;

	FVector Location = GetActorLocation() + (viewDirection * distanceInFront);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	float forwardImpulseIntensity = 500.0f;
	float upwardImpulseIntensity = 500.0f;
	FVector totalImpulse = (viewDirection * forwardImpulseIntensity) + (FVector::UpVector * upwardImpulseIntensity);

	if (healing)
	{
		if (healThrowable)
		{
			healThrowable = false;
			healCooldown = 1.5f;
			APotion* spawnedPotion = GetWorld()->SpawnActor<APotion>(potionClass, Location, Rotation, SpawnInfo);
			if (spawnedPotion && spawnedPotion->getMesh())
			{
				spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("heal on cooldown"));
		}
	}
	else
	{
		if (poisonThrowable)
		{
			poisonThrowable = false;
			poisonCooldown = 5.f;
			APoisonPotion* spawnedPotion = GetWorld()->SpawnActor<APoisonPotion>(poisonPotionClass, Location, Rotation, SpawnInfo);
			if (spawnedPotion && spawnedPotion->getMesh())
			{
				spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("poison on cooldown"));
		}
	}
}


void AVivianne::Sprint(const FInputActionValue& value)
{
	if (sprintReady)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sirpnt"));
		sprintDuration = 5.f;
		sprintCooldown = 15.f;
		GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
		sprinting = true;
		sprintReady = false;
	}
}

void AVivianne::Spell(const FInputActionValue& value)
{
}

void AVivianne::Ultimate(const FInputActionValue& value)
{

	APlayerCameraManager* playerCamera = GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->PlayerCameraManager : nullptr;


	FVector viewDirection = playerCamera->GetActorForwardVector();
	float distanceInFront = 50.0f;

	FVector Location = GetActorLocation() + (viewDirection * distanceInFront);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	float forwardImpulseIntensity = 500.0f;
	float upwardImpulseIntensity = 500.0f;
	FVector totalImpulse = (viewDirection * forwardImpulseIntensity) + (FVector::UpVector * upwardImpulseIntensity);

	if (ultimateReady)
	{
		ultimateReady = false;
		ultimateCooldown = 40.f;
		ACauldron* spawnedCauldron = GetWorld()->SpawnActor<ACauldron>(cauldronClass, Location, Rotation, SpawnInfo);
		if (spawnedCauldron && spawnedCauldron->getMesh())
		{
			spawnedCauldron->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
			spawnedCauldron->getHitbox()->AddImpulse(totalImpulse, NAME_None, true);
			// Lock rotation on the Z-axis (or any other axis as needed)
			spawnedCauldron->getMesh()->SetConstraintMode(EDOFMode::SixDOF);
			spawnedCauldron->getMesh()->GetBodyInstance()->bLockXRotation = true;
			spawnedCauldron->getMesh()->GetBodyInstance()->bLockYRotation = true;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ult on cooldown"));
	}
}

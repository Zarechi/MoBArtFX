// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Vivianne/Vivianne.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVivianne::AVivianne()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVivianne::BeginPlay()
{
	Super::BeginPlay();

	infos = Cast<UVivianneInfos>(GetPlayerDatas());
	if (infos.IsNull()) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, "info not initialized");
	GetCharacterMovement()->MaxWalkSpeed = infos->MaxWalkSpeed;
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
		GetCharacterMovement()->MaxWalkSpeed = infos->MaxWalkSpeed;
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

void AVivianne::Death_Implementation()
{
}

void AVivianne::AutoAttack_Implementation()
{
	Potion(true, infos->healingAmount);
}

void AVivianne::Spell_01_Implementation()
{
	Potion(false, infos->poisonAmount);
}

void AVivianne::Spell_02_Implementation()
{
	Sprint();
}

void AVivianne::Ultimate_Implementation()
{
	Ultimate();
}

void AVivianne::Reload_Implementation()
{
}



void AVivianne::Potion(bool healing, float amount)
{
	APlayerCameraManager* playerCamera = GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->PlayerCameraManager : nullptr;


	FVector viewDirection = playerCamera->GetActorForwardVector();
	float distanceInFront = 50.0f;

	FVector Location = GetActorLocation() + (viewDirection * distanceInFront);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FTransform SpawnTransform(Rotation, Location);
	FActorSpawnParameters SpawnInfo;

	float forwardImpulseIntensity = 500.0f;
	float upwardImpulseIntensity = 500.0f;
	FVector totalImpulse = (viewDirection * forwardImpulseIntensity) + (FVector::UpVector * upwardImpulseIntensity);

	if (healing)
	{
		if (healThrowable)
		{
			healThrowable = false;
			healCooldown = infos->AutoAttack_CD;
			APotion* spawnedPotion = GetWorld()->SpawnActorDeferred<APotion>(
				potionClass,
				SpawnTransform
			);

			if (spawnedPotion != nullptr)
			{
				spawnedPotion->setHealingAmount(infos->healingAmount);  // Set properties on the spawned puddle

				// Finalize the spawning process
				spawnedPotion->FinishSpawning(SpawnTransform);
			}
			spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
		}
	}
	else
	{
		if (poisonThrowable)
		{
			poisonThrowable = false;
			poisonCooldown = infos->Spell01_CD;
			APoisonPotion* spawnedPotion = GetWorld()->SpawnActorDeferred<APoisonPotion>(
				poisonPotionClass,
				SpawnTransform
			);

			if (spawnedPotion != nullptr)
			{
				spawnedPotion->setPoisonAmount(infos->poisonAmount);  // Set properties on the spawned puddle

				// Finalize the spawning process
				spawnedPotion->FinishSpawning(SpawnTransform);
			}
			spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
		}
	}
}


void AVivianne::Sprint()
{
	if (sprintReady)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sprint"));
		sprintDuration = infos->sprintDuration;
		sprintCooldown = infos->Spell02_CD;
		GetCharacterMovement()->MaxWalkSpeed = infos->sprintSpeed;
		sprinting = true;
		sprintReady = false;
	}
}

void AVivianne::Ultimate()
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
		ultimateCooldown = infos->Ultimate_CD;
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
}
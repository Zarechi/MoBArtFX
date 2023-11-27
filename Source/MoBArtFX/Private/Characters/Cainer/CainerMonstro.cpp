#include "Characters/Cainer/CainerMonstro.h"
#include "GameFramework/CharacterMovementComponent.h"


ACainerMonstro::ACainerMonstro()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACainerMonstro::BeginPlay()
{
	Super::BeginPlay();
	
	aiController = GetWorld()->SpawnActor<AAIC_CainerMonstro>(aiControllerClass_, FTransform());
	aiController->Possess(this);
}

void ACainerMonstro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		if (!aiController->IsMoving())
		{
			isMoving = false;
			aiController->Stop();

			FRotator rotation = GetActorRotation();
			rotation.Yaw = wantedYawRotation;
			SetActorRotation(rotation);
		}
		return;
	}
}


void ACainerMonstro::SetSpeed(float speed)
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = speed;
}

void ACainerMonstro::SetLife(float life)
{
	health = life;
}


void ACainerMonstro::SetDestination(FVector destination, float yawRotation)
{
	isMoving = aiController->SetDestination(destination);

	wantedYawRotation = yawRotation;

	if (isMoving) return;

	FRotator rotation = GetActorRotation();
	rotation.Yaw = wantedYawRotation;
	SetActorRotation(rotation);
}


void ACainerMonstro::TakeDamage(float damage)
{
	health -= damage;
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::White, "Monstro took " + FString::SanitizeFloat(damage) + " damages.");

	if (health <= 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::White, "Monstro died.");
		Destroy();
	}
}

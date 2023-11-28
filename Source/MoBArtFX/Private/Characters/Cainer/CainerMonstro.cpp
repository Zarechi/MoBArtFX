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

float ACainerMonstro::TakeDamage(const float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage_taken = fmax(health, Damage);

	health -= Damage;
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::White, "Monstro took " + FString::SanitizeFloat(Damage) + " damages.");

	if (health <= 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::White, "Monstro died.");
		Destroy();
	}

	return damage_taken; 
}

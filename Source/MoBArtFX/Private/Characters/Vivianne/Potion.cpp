// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Vivianne/Potion.h"

// Sets default values
APotion::APotion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	potionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PotionMesh"));




}

void APotion::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector Location = Hit.ImpactPoint + FVector(0, 0, 10);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	// Create a FTransform with the location and rotation
	FTransform SpawnTransform(Rotation, Location);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// Spawn the actor deferred
	APotionPuddle* spawnedPuddle = GetWorld()->SpawnActorDeferred<APotionPuddle>(
		puddleClass,
		SpawnTransform
	);

	if (spawnedPuddle != nullptr)
	{
		spawnedPuddle->setHealing(true);  // Set properties on the spawned puddle
		spawnedPuddle->setHealingAmount(healingAmount);

		// Finalize the spawning process
		spawnedPuddle->FinishSpawning(SpawnTransform);
		Destroy();
	}


}

// Called when the game starts or when spawned
void APotion::BeginPlay()
{
	Super::BeginPlay();
	potionMesh->OnComponentHit.AddDynamic(this, &APotion::OnHit);

}

// Called every frame
void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


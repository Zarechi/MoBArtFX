// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Vivianne/PoisonPotion.h"

// Sets default values
APoisonPotion::APoisonPotion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	poisonPotionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PoisonPotionMesh"));




}

void APoisonPotion::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
		spawnedPuddle->setHealing(false);  // Set properties on the spawned puddle
		spawnedPuddle->setPoisonAmount(poisonAmount);

		// Finalize the spawning process
		spawnedPuddle->FinishSpawning(SpawnTransform);
		Destroy();
	}


}

// Called when the game starts or when spawned
void APoisonPotion::BeginPlay()
{
	Super::BeginPlay();
	poisonPotionMesh->OnComponentHit.AddDynamic(this, &APoisonPotion::OnHit);

}

// Called every frame
void APoisonPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


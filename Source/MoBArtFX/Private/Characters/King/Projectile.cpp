// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include <Characters/King/Int_Interaction_Chara.h>

// Sets default values
AProjectile::AProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	//CollisionComp->BodyInstance.SetInstanceNotifyRBCollision(true);
	//CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComp->SetSphereRadius(10);

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meshprojectile"));
	projectileMesh->SetupAttachment(CollisionComp);
	projectileMesh->SetRelativeScale3D(FVector(0.285f, 0.15f, 0.15f));


	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0;

	// Die after 3 seconds by default
	InitialLifeSpan = 0.3f;

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		if (OtherActor->Implements<UInt_Interaction_Chara>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("IronShears"));
			IInt_Interaction_Chara::Execute_DoDamage(OtherActor);
		}
		Destroy();
	}
}


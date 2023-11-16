#include "Characters/Crow/Crow_Projectile.h"

ACrow_Projectile::ACrow_Projectile()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create shape of the projectile
	FeatherMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FeatherMesh"));
	RootComponent = FeatherMesh;

	// Create static mesh for projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultSphereMesh(TEXT("Content/Characters/Crow/Models/ST_Plume"));
	if (DefaultSphereMesh.Succeeded())
	{
		FeatherMesh->SetStaticMesh(DefaultSphereMesh.Object);
	}

	// Configure material
	static ConstructorHelpers::FObjectFinder<UMaterial> ProjectileMaterial(TEXT("Content/Characters/Crow/Models/lambert2"));
	if (ProjectileMaterial.Succeeded())
	{
		FeatherMesh->SetMaterial(0, ProjectileMaterial.Object);
	}

	//PARAMETERS BY DEFAULT
	ProjectileSpeed = 2000.0f;
	ProjectileLifetime = 10.0f;
	ProjectileSize = FVector(1.0f, 1.0f, 1.0f);

	FeatherMesh->SetWorldScale3D(ProjectileSize);

}

void ACrow_Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void ACrow_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Projectile Movement
	MoveProjectile(DeltaTime);

	// Time since creation
	ProjectileLifetime -= DeltaTime;

	// Destroy projectile
	if (ProjectileLifetime <= 0.0f)
	{
		Destroy();
	}
}

// Function to define the direction of projectile
void ACrow_Projectile::SetDirection(const FVector& NewDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("SetDirection: %s"), *NewDirection.ToString());
	MoveDirection = NewDirection.GetSafeNormal(); // Normalize direction
}

void ACrow_Projectile::SetProjectileSpeed(float NewSpeed)
{
	ProjectileSpeed = NewSpeed;
}

void ACrow_Projectile::SetProjectileLifetime(float NewLifetime)
{
	ProjectileLifetime = NewLifetime;
}


// Function that manage the movement
void ACrow_Projectile::MoveProjectile(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + MoveDirection * ProjectileSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

#include "MOBA_Projectile.h"

AMOBA_Projectile::AMOBA_Projectile()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create shape of the projectile
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	RootComponent = SphereMesh;
	
	// Create static mesh for projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultSphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (DefaultSphereMesh.Succeeded())
	{
		SphereMesh->SetStaticMesh(DefaultSphereMesh.Object);
	}

	// Configure material
	static ConstructorHelpers::FObjectFinder<UMaterial> ProjectileMaterial(TEXT("Content/Materials/MT_Projectile"));
	if (ProjectileMaterial.Succeeded())
	{
		SphereMesh->SetMaterial(0, ProjectileMaterial.Object);
	}

	//PARAMETERS BY DEFAULT
	ProjectileSpeed = 2000.0f;
	ProjectileLifetime = 10.0f;
	ProjectileSize = FVector(1.0f, 0.05f, 0.05f);

	SphereMesh->SetWorldScale3D(ProjectileSize);

}

void AMOBA_Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void AMOBA_Projectile::Tick(float DeltaTime)
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
void AMOBA_Projectile::SetDirection(const FVector& NewDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("SetDirection: %s"), *NewDirection.ToString());
	MoveDirection = NewDirection.GetSafeNormal(); // Normalize direction
}

void AMOBA_Projectile::SetProjectileSpeed(float NewSpeed)
{
	ProjectileSpeed = NewSpeed;
}

void AMOBA_Projectile::SetProjectileLifetime(float NewLifetime)
{
	ProjectileLifetime = NewLifetime;
}


// Function that manage the movement
void AMOBA_Projectile::MoveProjectile(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + MoveDirection * ProjectileSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

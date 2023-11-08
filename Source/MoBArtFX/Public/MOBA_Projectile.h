#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOBA_Projectile.generated.h"

UCLASS()
class MOBARTFX_API AMOBA_Projectile : public AActor
{
	GENERATED_BODY()

public:

	AMOBA_Projectile();
	virtual void Tick(float DeltaTime) override;

	// Configurez la fonction pour définir la direction du mouvement du projectile
	void SetDirection(const FVector& NewDirection);

protected:

	virtual void BeginPlay() override;

private:

	// Projectile Shape
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* SphereMesh;

	// Projectile Speed
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileSpeed;

	// Projectile Lifetime
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileLifetime;

	// Projectile Size
	UPROPERTY(EditAnywhere, Category = "Projectile")
	FVector ProjectileSize;

	// Projectile Direction
	FVector MoveDirection;

	// Manage movements
	void MoveProjectile(float DeltaTime);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IronShears.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class MOBARTFX_API AIronShears : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Projectile)
	TObjectPtr<UBoxComponent> CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
public:	
	// Sets default values for this actor's properties
	AIronShears();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

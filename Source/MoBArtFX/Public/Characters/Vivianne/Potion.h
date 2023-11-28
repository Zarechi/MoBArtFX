// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionPuddle.h"
#include "Potion.generated.h"

UCLASS()
class MOBARTFX_API APotion : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere);
	TSubclassOf<APotionPuddle> puddleClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* potionMesh;
	// Sets default values for this actor's properties
	APotion();

	UStaticMeshComponent* getMesh() { return potionMesh; }
	void setHealingAmount(float amount) { healingAmount = amount; }

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	float healingAmount;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

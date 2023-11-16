// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionPuddle.h"
#include "PoisonPotion.generated.h"

UCLASS()
class MOBARTFX_API APoisonPotion : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere);
	TSubclassOf<APotionPuddle> puddleClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* poisonPotionMesh;
	// Sets default values for this actor's properties
	APoisonPotion();

	UStaticMeshComponent* getMesh() { return poisonPotionMesh; }
	void setPoisonAmount(float amount) { poisonAmount = amount; }

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	float poisonAmount;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


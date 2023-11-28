// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cauldron.generated.h"

UCLASS()
class MOBARTFX_API ACauldron : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* cauldronMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* hitbox;

	bool bRotationCorrected;


	// Sets default values for this actor's properties
	ACauldron();

	UStaticMeshComponent* getMesh() { return cauldronMesh; }
	UStaticMeshComponent* getHitbox() { return hitbox; }

protected:
	FTimerHandle RotationCorrectionTimer;

	void CorrectRotation();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	void Tick(float DeltaTime) override;

};

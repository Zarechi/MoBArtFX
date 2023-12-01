// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "PotionPuddle.generated.h"


UCLASS()
class MOBARTFX_API APotionPuddle : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* puddleMesh;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* HealNiagara;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* PoisonNiagara;

	// Sets default values for this actor's properties
	APotionPuddle();

	UStaticMeshComponent* getMesh() { return puddleMesh; }
	void setHealing(bool healingP);
	void setHealingAmount(float amount) { healingAmount = amount; }
	void setPoisonAmount(float amount) { poisonAmount = amount; }

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	float puddleTimer;
	bool healing;

	float healingAmount;
	float poisonAmount;
;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	void Tick(float DeltaTime) override;

};

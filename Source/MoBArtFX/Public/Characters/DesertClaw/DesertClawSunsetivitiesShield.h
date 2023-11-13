#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawSunsetivitiesShield.generated.h"

UCLASS()
class MOBARTFX_API ADesertClawSunsetivitiesShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADesertClawSunsetivitiesShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

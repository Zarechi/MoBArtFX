

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertClawSunsetivitiesGrenade.generated.h"

UCLASS()
class MOBARTFX_API ADesertClawSunsetivitiesGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADesertClawSunsetivitiesGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

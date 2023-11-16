

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_AttackType.h"
#include "Needle.generated.h"

UCLASS()
class MOBARTFX_API ANeedle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeedle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	double Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TEnumAsByte<AttackType> Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	AActor* Player;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	bool IsSkillShot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	bool IsTeleport;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float SlownessDelay = 2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float StunDelay = 1.0f;
};

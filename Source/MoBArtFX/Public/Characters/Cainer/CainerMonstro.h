#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIC_CainerMonstro.h"
#include "CainerMonstro.generated.h"

UCLASS()
class MOBARTFX_API ACainerMonstro : public ACharacter
{
	GENERATED_BODY()

public:
	ACainerMonstro();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	TSubclassOf<AAIC_CainerMonstro> aiControllerClass_;

	void SetBaseSpeed(float speed);
	void SetLife(float life);
	void SetDestination(FVector destination, float yawRotation);
	void BoostSpeed(float boost, float boostTime);

	UFUNCTION(BlueprintCallable)
	float TakeDamage(const float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<AAIC_CainerMonstro> aiController;

	float health{ 0.0f };
	float basespeed{ 0.0f };
	bool isMoving{ false };
	float boostTimer{ 0.0f };

	float wantedYawRotation{ 0.0f };
};

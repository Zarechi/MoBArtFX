

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "E_AttackType.h"
#include "Components/ActorComponent.h"
#include "Needle_Damage_System.generated.h"

class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBARTFX_API UNeedle_Damage_System : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNeedle_Damage_System();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Hit(TEnumAsByte<AttackType> type, float damage);

	UFUNCTION(BlueprintCallable)
	void SkillShotHit(float SlownessDelay, float StunDelay);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	TArray <TEnumAsByte<AttackType>> needleStack;
private:
	void ApplyDmg(float damage);

	float slowDownCurrentCooldown = 0;
	float stunCurrentCooldown = 0;

	float poisonDamage = 0;
	float antiHealCurrentCooldown = 0;
	float normalMoveSpeed = 0;

	UCharacterMovementComponent* charMov;
};

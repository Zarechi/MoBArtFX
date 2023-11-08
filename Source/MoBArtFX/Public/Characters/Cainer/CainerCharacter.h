#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include <Particles/ParticleSystem.h>
#include "CainerInfos.h"
#include "CainerMonstro.h"
#include "CainerCharacter.generated.h"


UCLASS()
class MOBARTFX_API ACainerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ACainerCharacter();

	virtual void Tick(float DeltaTime) override;


	void Death_Implementation() override;
	void AutoAttack_Implementation() override;
	void Spell_01_Implementation() override;
	void Spell_02_Implementation() override;
	void Ultimate_Implementation() override;
	void Reload_Implementation() override;


protected:
	virtual void BeginPlay() override;


	UFUNCTION( BlueprintCallable, BlueprintPure )
	ACainerMonstro* GetMonstro() const { return monstro; }


private:
	// Cooldowns
	float monstroCrtCD = 0.0f;
	float speedBoostCrtCD = 0.0f;
	float flashCrtCD = 0.0f;

	TObjectPtr<UCainerInfos> infos;
	TObjectPtr<ACainerMonstro> monstro;

	FVector GetMonstroDestination();
};

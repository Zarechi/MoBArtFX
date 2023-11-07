#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MobaAbilityData.h"
#include "MobaAbility.generated.h"

class ADesertClawCharacter;

USTRUCT( BlueprintType )
struct FMobaAbilityRunContext
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	bool IsOverridenSlot = false;

	UPROPERTY( BlueprintReadOnly )
	bool IsStartInput = true;
};

/*
 *	Ability
 */
UCLASS( Blueprintable, BlueprintType )
class MOBARTFX_API UMobaAbility : public UObject
{
	GENERATED_BODY()

public:
	void Setup( ADesertClawCharacter* character, UMobaAbilityData* data, EMobaAbilitySlot slot );
	void Initialize();

	UFUNCTION( BlueprintCallable, Category = "Ability" )
	bool Run( FMobaAbilityRunContext context );
	UFUNCTION( BlueprintCallable, Category = "Ability" )
	void Tick( float dt );

	/*
	 *  Called when the ability is initialized. Accessing different abilities from here will work as expected.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnInitialize();
	virtual void OnInitialize_Implementation() {}
	/*
	 *  Called when the ability is activated, most likely via input.
	 *  On kMobaAbilityMode::ON_OFF mode, the OnRun is called when IsActive is equal to true.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnRun( FMobaAbilityRunContext context );
	virtual void OnRun_Implementation( FMobaAbilityRunContext context );
	/*
	 *  Called only in kMobaAbilityMode::ON_OFF mode, when IsActive is equal to false.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnStop( FMobaAbilityRunContext context );
	virtual void OnStop_Implementation( FMobaAbilityRunContext context ) {}
	/*
	 *  Called for each tick.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnTick( float delta_time );
	virtual void OnTick_Implementation( float dt ) {}

	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Ability" )
	bool IsOnCooldown() { return Cooldown > 0.0f; }
	UFUNCTION( BlueprintCallable, Category = "Ability" )
	void SetCooldown( float cooldown ) { Cooldown = cooldown; }
	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Ability" )
	float GetCooldown() { return Cooldown; }

	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Ability" )
	UMobaAbilityData* GetData() { return Data; }
	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Ability" )
	ADesertClawCharacter* GetCharacter() { return Character; }
	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Ability" )
	FString GetName() const;

	UPROPERTY( BlueprintReadOnly, Category = "Ability" )
	EMobaAbilityMode Mode = EMobaAbilityMode::Single;
	UPROPERTY( BlueprintReadOnly, Category = "Ability" )
	EMobaAbilitySlot Slot = EMobaAbilitySlot::First;

	UWorld* GetWorld() const override;

protected:
	ADesertClawCharacter* Character;
	UMobaAbilityData* Data;

	//  Exclusive to kMobaAbilityMode::ON_OFF mode, represents if the ability is active or not
	UPROPERTY( BlueprintReadOnly, Category = "Ability", meta = ( AllowPrivateAccess = true ) )
	bool IsActive = false;

	//  Time in seconds before being able to use the ability again
	UPROPERTY( BlueprintReadOnly, Category = "Ability", meta = ( AllowPrivateAccess = true ) )
	float Cooldown = 0.0f;
};

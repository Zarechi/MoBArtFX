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
	/*
	 *  Called when the ability is activated, most likely via input.
	 *  On EMobaAbilityMode::OnOff mode, the OnRun is called when IsActive is equal to true.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnRun( FMobaAbilityRunContext context );
	/*
	 *  Called only in EMobaAbilityMode::OnOff mode, when IsActive is equal to false.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnStop( FMobaAbilityRunContext context );
	/*
	 *  Called for each tick.
	 */
	UFUNCTION( BlueprintNativeEvent )
	void OnTick( float delta_time );

	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Ability" )
	bool IsOnCooldown() { return Cooldown > 0.0f; }
	UFUNCTION( BlueprintCallable, Category = "Ability" )
	void SetCooldown( float cooldown ) { Cooldown = cooldown; }
	UFUNCTION( BlueprintCallable, Category = "Ability" )
	void ResetCooldown();
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

	//  Exclusive to EMobaAbilityMode::OnOff mode, represents if the ability is active or not
	UPROPERTY( BlueprintReadOnly, Category = "Ability", meta = ( AllowPrivateAccess = true ) )
	bool IsActive = false;

	//  Time in seconds before being able to use the ability again
	UPROPERTY( BlueprintReadOnly, Category = "Ability", meta = ( AllowPrivateAccess = true ) )
	float Cooldown = 0.0f;
};

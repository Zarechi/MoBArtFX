#pragma once

#include "CoreMinimal.h"
#include "Engine/DamageEvents.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MobaGameplayStatics.generated.h"

class ABaseCharacter;


UENUM(BlueprintType)
enum class EMobaTeam : uint8
{
	NONE = 0,
	BLUE = 1,
	RED = 2
};


USTRUCT(BlueprintType)
struct FMobaDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

	FMobaDamageEvent();
	FMobaDamageEvent(ABaseCharacter* Instigator);
	FMobaDamageEvent(ABaseCharacter* Instigator, FDamageEvent const& InDamageEvent);

	ABaseCharacter* CharacterInstigator;
	EMobaTeam Team;


	/** ID for this class. NOTE this must be unique for all damage events. */
	static const int32 ClassID = 134;

	virtual int32 GetTypeID() const override { return FMobaDamageEvent::ClassID; };
	virtual bool IsOfType(int32 InID) const override { return (FMobaDamageEvent::ClassID == InID) || FDamageEvent::IsOfType(InID); };
};


UCLASS()
class MOBARTFX_API UMobaGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Hurts the specified actor with moba specific damage.
	 * @param DamagedActor - Actor that will be damaged.
	 * @param BaseDamage - The base damage to apply.
	 * @param DamageCauser - Actor that actually caused the damage (e.g. the grenade that exploded)
	 * @param CharacterInstigator - Base Character that is at the origin of this damage.
	 * @return Actual damage the ended up being applied to the actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Game|Damage")
	static float ApplyMobaDamage(AActor* DamagedActor, float BaseDamage, AActor* DamageCauser, ABaseCharacter* CharacterInstigator);
};

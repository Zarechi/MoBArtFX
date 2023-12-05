#include "MobaGameplayStatics.h"
#include "BaseCharacter.h"

FMobaDamageEvent::FMobaDamageEvent() : 
	FDamageEvent(), Team(EMobaTeam::NONE) 
{}

FMobaDamageEvent::FMobaDamageEvent(ABaseCharacter* Instigator) : 
	FDamageEvent(), CharacterInstigator(Instigator), Team(Instigator->GetTeam()) 
{}

FMobaDamageEvent::FMobaDamageEvent(ABaseCharacter* Instigator, FDamageEvent const& InDamageEvent) : 
	FDamageEvent(InDamageEvent), CharacterInstigator(Instigator), Team(Instigator->GetTeam()) 
{}


float UMobaGameplayStatics::ApplyMobaDamage(AActor* DamagedActor, float BaseDamage, AActor* DamageCauser, ABaseCharacter* CharacterInstigator)
{
	if (DamagedActor && (BaseDamage != 0.0f))
	{
		FMobaDamageEvent DamageEvent(CharacterInstigator);

		return DamagedActor->TakeDamage(BaseDamage, DamageEvent, CharacterInstigator->GetController(), DamageCauser);
	}

	return 0.0f;
}

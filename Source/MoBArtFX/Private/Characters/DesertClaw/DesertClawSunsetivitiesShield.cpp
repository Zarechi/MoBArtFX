#include "Characters/DesertClaw/DesertClawSunsetivitiesShield.h"
#include "Characters/DesertClaw/DesertClawSunsetivitiesAbility.h"

ADesertClawSunsetivitiesShield::ADesertClawSunsetivitiesShield()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADesertClawSunsetivitiesShield::Activate( float time )
{
	SetLifeSpan( time );
}

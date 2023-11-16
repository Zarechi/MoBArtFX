#include "Characters/DesertClaw/DesertClawUltimateDecal.h"

ADesertClawUltimateDecal::ADesertClawUltimateDecal()
{
	PrimaryActorTick.bCanEverTick = false;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>( TEXT( "Decal Component" ) );
	RootComponent = DecalComponent;
}

void ADesertClawUltimateDecal::SetupAbility( UDesertClawUltimateAbility* ability )
{
	Ability = ability;
}

void ADesertClawUltimateDecal::BeginPlay()
{
	Super::BeginPlay();
}

void ADesertClawUltimateDecal::Tick( float dt )
{
	Super::Tick( dt );
}


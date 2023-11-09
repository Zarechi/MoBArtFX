#include "Characters/DesertClaw/DesertClawUltimateDecal.h"

ADesertClawUltimateDecal::ADesertClawUltimateDecal()
{
	PrimaryActorTick.bCanEverTick = false;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>( TEXT( "Decal Component" ) );
}

void ADesertClawUltimateDecal::BeginPlay()
{
	Super::BeginPlay();
}

void ADesertClawUltimateDecal::Tick( float dt )
{
	Super::Tick( dt );
}


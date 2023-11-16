#include "Characters/DesertClaw/DesertClawSunsetivitiesGrenade.h"

// Sets default values
ADesertClawSunsetivitiesGrenade::ADesertClawSunsetivitiesGrenade()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
	RootComponent = Mesh;
}

void ADesertClawSunsetivitiesGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADesertClawSunsetivitiesGrenade::Tick( float dt )
{
	Super::Tick( dt );

}


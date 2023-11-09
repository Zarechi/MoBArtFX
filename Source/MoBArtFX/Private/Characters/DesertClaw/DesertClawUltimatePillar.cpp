
#include "Characters/DesertClaw/DesertClawUltimatePillar.h"
#include "Characters/DesertClaw/DesertClawUltimateAbility.h"

ADesertClawUltimatePillar::ADesertClawUltimatePillar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADesertClawUltimatePillar::SetupData( UDesertClawUltimateAbilityData* data )
{
	Data = data;
}

void ADesertClawUltimatePillar::TriggerFall()
{
	IsFalling = true;

	SetActorTickEnabled( true );

	//  stop fall by time
	GetWorldTimerManager().SetTimer( 
		StopTimerHandle, 
		this, &ADesertClawUltimatePillar::StopFall, 
		Data->PillarStopTime, false
	);
}

void ADesertClawUltimatePillar::StopFall()
{
	IsFalling = false;

	SetActorTickEnabled( false );

	//  teleport pillar far away
	SetActorLocation( FVector { 0.0f, 0.0f, -5000.0f } );

	//  clear fall timer
	GetWorldTimerManager().ClearTimer( StopTimerHandle );
}

void ADesertClawUltimatePillar::BeginPlay()
{
	Super::BeginPlay();

	StopFall();
}

void ADesertClawUltimatePillar::Tick( float dt )
{
	Super::Tick( dt );

	AddActorWorldOffset( 
		FVector { 
			0.0f, 
			0.0f, 
			-Data->PillarFallSpeed * dt 
		},
		true
	);
}


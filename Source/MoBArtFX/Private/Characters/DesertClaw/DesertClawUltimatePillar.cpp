
#include "Characters/DesertClaw/DesertClawUltimatePillar.h"
#include "Characters/DesertClaw/DesertClawUltimateAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "Defines.h"
#include "Engine/DamageEvents.h"
#include "MobaGameplayStatics.h"

ADesertClawUltimatePillar::ADesertClawUltimatePillar()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
	RootComponent = Mesh;
}

void ADesertClawUltimatePillar::SetupAbility( UDesertClawUltimateAbility* ability )
{
	Ability = ability;
	CustomData = ability->GetCustomData();
}

void ADesertClawUltimatePillar::TriggerFall()
{
	IsFalling = true;

	SetActorTickEnabled( true );
	SetActorEnableCollision( true );
	SetActorHiddenInGame( false );

	//  stop fall by time
	GetWorldTimerManager().SetTimer( 
		StopTimerHandle, 
		this, &ADesertClawUltimatePillar::StopFall, 
		CustomData->PillarStopTime, false
	);
}

void ADesertClawUltimatePillar::StopFall()
{
	IsFalling = false;

	SetActorTickEnabled( false );
	SetActorEnableCollision( false );
	SetActorHiddenInGame( true );

	//  teleport pillar far away
	SetActorLocation( CustomData->PillarDefaultLocation );

	//  clear fall timer
	GetWorldTimerManager().ClearTimer( StopTimerHandle );
}

void ADesertClawUltimatePillar::BeginPlay()
{
	Super::BeginPlay();

	//  bind event
	Mesh->OnComponentBeginOverlap.AddUniqueDynamic( 
		this, 
		&ADesertClawUltimatePillar::OnMeshBeginOverlap 
	);
}

void ADesertClawUltimatePillar::Tick( float dt )
{
	Super::Tick( dt );

	AddActorWorldOffset( 
		FVector { 
			0.0f, 
			0.0f, 
			-CustomData->PillarFallSpeed * dt 
		},
		true
	);
}

void ADesertClawUltimatePillar::OnMeshBeginOverlap( 
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult 
)
{
	UMobaGameplayStatics::ApplyMobaDamage(
		OtherActor,
		CustomData->PillarDamage,
		this,
		Ability->GetCharacter()
	);
}


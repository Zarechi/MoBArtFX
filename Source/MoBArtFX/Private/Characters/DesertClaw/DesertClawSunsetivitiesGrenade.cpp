#include "Characters/DesertClaw/DesertClawSunsetivitiesGrenade.h"
#include "Characters/DesertClaw/DesertClawSunsetivitiesAbility.h"

#include "Defines.h"

ADesertClawSunsetivitiesGrenade::ADesertClawSunsetivitiesGrenade()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
	Mesh->SetSimulatePhysics( true );
	Mesh->SetNotifyRigidBodyCollision( true );
	RootComponent = Mesh;
}

void ADesertClawSunsetivitiesGrenade::SetupData( UDesertClawSunsetivitiesAbilityData* data )
{
	CustomData = data;

	TriggerTime = CustomData->GrenadeTriggerTime;
}

void ADesertClawSunsetivitiesGrenade::BeginPlay()
{
	Super::BeginPlay();
	
	//SpawnRotation.Roll = 90.0f;
	SpawnRotation.Yaw = GetActorRotation().Yaw;

	Mesh->OnComponentHit.AddDynamic( this, &ADesertClawSunsetivitiesGrenade::OnMeshHit );
}

void ADesertClawSunsetivitiesGrenade::Tick( float dt )
{
	Super::Tick( dt );

	TriggerTime -= dt;
	if ( TriggerTime <= 0.0f )
	{
		auto world = GetWorld();
		auto shield = world->SpawnActor<ADesertClawSunsetivitiesShield>(
			CustomData->ShieldActorClass,
			GetActorLocation(),
			SpawnRotation
		);
		shield->Activate( CustomData->ShieldTime );

		SetActorTickEnabled( false );
	}
}

void ADesertClawSunsetivitiesGrenade::OnMeshHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if ( IsTriggered ) return;

	//  check surface normal
	NormalImpulse.Normalize();
	float surface_dot = NormalImpulse.Dot( FVector { 0.0f, 0.0f, 1.0f } );
	if ( !FMath::IsNearlyEqual( surface_dot, 1.0f, 0.3f ) ) return;

	//  trigger
	SetActorTickEnabled( true );
	Mesh->SetLinearDamping( 5.0f );
	Mesh->SetAngularDamping( 3.0f );

	IsTriggered = true;
}


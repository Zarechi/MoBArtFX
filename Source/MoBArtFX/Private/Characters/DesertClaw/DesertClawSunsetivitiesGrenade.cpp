#include "Characters/DesertClaw/DesertClawSunsetivitiesGrenade.h"
#include "Characters/DesertClaw/DesertClawSunsetivitiesAbility.h"

ADesertClawSunsetivitiesGrenade::ADesertClawSunsetivitiesGrenade()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
	Mesh->SetSimulatePhysics( true );
	RootComponent = Mesh;
}

void ADesertClawSunsetivitiesGrenade::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnRotation.Roll = 90.0f;
	SpawnRotation.Yaw = GetActorRotation().Yaw;

	Mesh->OnComponentHit.AddDynamic( this, &ADesertClawSunsetivitiesGrenade::OnMeshHit );
}

void ADesertClawSunsetivitiesGrenade::Tick( float dt )
{
	Super::Tick( dt );

	TriggerTime -= dt;
	if ( TriggerTime <= 0.0f )
	{
		auto shield = GetWorld()->SpawnActor<ADesertClawSunsetivitiesShield>(
			CustomData->ShieldActorClass,
			GetActorLocation(),
			SpawnRotation
		);
		shield->Activate();

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

	NormalImpulse.Normalize();
	float surface_dot = NormalImpulse.Dot( FVector { 0.0f, 0.0f, -1.0f } );

	if ( !FMath::IsNearlyEqual( surface_dot, 1.0f, 0.3f ) ) return;

	SetActorTickEnabled( true );
	Mesh->SetLinearDamping( 5.0f );
	Mesh->SetAngularDamping( 3.0f );

	IsTriggered = true;
}


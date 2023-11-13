#include "Characters/DesertClaw/DesertClawUltimateAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "ActorSequence.h"
#include "ActorSequencePlayer.h"
#include "Defines.h"

void UDesertClawUltimateAbility::OnInitialize_Implementation()
{
	CustomData = CastChecked<UDesertClawUltimateAbilityData>( Data );

	PassiveAbility = CastChecked<UDesertClawPassiveAbility>( Character->GetAbility( EMobaAbilitySlot::Passive ) );

	SpawnDecal();
	SpawnPillars();
}

void UDesertClawUltimateAbility::OnTick_Implementation( float dt )
{
	if ( !IsActive ) return;

	auto controller = Character->GetPlayerController();
	
	//  setup params
	FCollisionQueryParams query_params;
	query_params.AddIgnoredActor( Character );
	FCollisionResponseParams response_params;

	//  performs trace
	FHitResult result;
	controller->CameraTraceSingleByChannel( 
		result, 
		CustomData->PlacementRange, 
		CustomData->PlacementCollisionChannel,
		query_params,
		response_params
	);
	if ( result.bBlockingHit )
	{
		DecalActor->SetActorLocation( result.Location );
	}
		
	//  startup timer
	//  TODO: refactor w/ an Unreal timer
	if ( ( StartupTime -= dt ) <= 0.0f )
	{
		EndStartup();
		return;
	}

	//  TODO: update startup timer HUD
}

void UDesertClawUltimateAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{
	BeginStartup();
}

void UDesertClawUltimateAbility::OnStop_Implementation( FMobaAbilityRunContext context )
{
	EndStartup();
}

void UDesertClawUltimateAbility::TriggerNextPillar()
{
	kPRINT( "Trigger pillar " + FString::FromInt( CurrentPillarIndex ) );

	TriggerPillar( CurrentPillarIndex );
	CurrentPillarIndex++;
}

void UDesertClawUltimateAbility::TriggerPillar( int index )
{
	//kSAFE_ASSERT_TEXT( Pillars.IsValidIndex( index ), "Ultimate: couldn't Trigger Pillar with index " + FString::FromInt( index ) + ", out of bounds!" );
	check( Pillars.IsValidIndex( index ) );

	//  get pillar spawn location
	FVector location = DecalActor->GetSpawnLocation( index );
	location.Z += CustomData->PillarSpawnOffsetZ;

	//  trigger pillar
	auto pillar = Pillars[index];
	pillar->SetActorLocation( location );
	pillar->TriggerFall();
}

void UDesertClawUltimateAbility::BeginStartup()
{	
	IsActive = true;

	StartupTime = CustomData->StartupTime;

	//  show in game
	DecalActor->SetActorHiddenInGame( false );

	kPRINT( "Ultimate: Begin Startup" );
}

void UDesertClawUltimateAbility::EndStartup()
{
	IsActive = false;

	BeginFall();

	//  reset active slot
	Character->ResetAbilitySlot( Data->ActiveOverrideSlot );

	kPRINT( "Ultimate: End Startup" );
}

void UDesertClawUltimateAbility::BeginFall()
{
	//  play fall sequence
	CurrentPillarIndex = 0;
	UActorSequenceComponent* sequence_component = DecalActor->GetSequenceComponent();
	sequence_component->PlaySequence();

	kPRINT( "Ultimate: Begin Fall" );
}

void UDesertClawUltimateAbility::EndFall()
{
	//  schedule refill
	RefillGaugeAfterDelay();

	//  hide decal
	DecalActor->SetActorHiddenInGame( true );

	kPRINT( "Ultimate: End Fall" );
}

void UDesertClawUltimateAbility::RefillGaugeAfterDelay()
{
	FTimerHandle handle;
	Character->GetWorldTimerManager().SetTimer( 
		handle,
		this, 
		&UDesertClawUltimateAbility::RefillGauge, 
		CustomData->RefillDelay, 
		false 
	);
}

void UDesertClawUltimateAbility::RefillGauge()
{
	PassiveAbility->AddSandPercent( 1.0f );

	kPRINT( "Ultimate: Refill Gauge" );
}

void UDesertClawUltimateAbility::SpawnDecal()
{
	//  spawn decal actor
	DecalActor = GetWorld()->SpawnActor<ADesertClawUltimateDecal>( 
		CustomData->DecalActorClass,
		FVector( 0.0f, 0.0f, 0.0f ),
		FRotator( 0.0f, 0.0f, 0.0f )
	);
	DecalActor->SetupAbility( this );

	//  set scale
	FVector scale = GetDecalScaleFromSize( 
		CustomData->DecalRadius, 
		CustomData->DecalHeight 
	);
	DecalActor->SetActorScale3D( scale );

	//  hide in game
	DecalActor->SetActorHiddenInGame( true );
}

FVector UDesertClawUltimateAbility::GetDecalScaleFromSize( float radius, float height )
{
	/*
	 *  For some reasons, the decal is 90° pitch-rotated so:
	 *  - YZ is Radius
	 *  - X is height
	 */
	FVector decal_size = DecalActor->GetDecalComponent()->DecalSize;
	return FVector(
		height / decal_size.X,
		radius / decal_size.Y,
		radius / decal_size.Y
	);
}

void UDesertClawUltimateAbility::SpawnPillars()
{
	UWorld* world = GetWorld();

	//  get pillar radius
	float radius = CustomData->DecalRadius;
	radius *= 2.0f;   //  radius to diameter
	radius /= 3.0f;   //  decal is divided in 3 circles
	radius *= 0.01f;  //  centimeters to meters

	//  get pillar scale
	FVector scale { 
		radius, 
		radius, 
		CustomData->PillarHeight 
	};

	//  spawn pillars
	for ( int i = 0; i < DecalActor->GetSpawnCount(); i++ )
	{
		auto pillar = world->SpawnActor<ADesertClawUltimatePillar>( 
			CustomData->PillarActorClass
			//CustomData->PillarDefaultLocation,  //  position is set automatically in StopFall
			//FRotator::ZeroRotator
		);
		pillar->SetupAbility( this );
		pillar->Mesh->SetRelativeScale3D( scale );
		pillar->StopFall();

		Pillars.Add( pillar );
	}
}
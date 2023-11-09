#include "Characters/DesertClaw/DesertClawUltimateAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "Defines.h"

void UDesertClawUltimateAbility::OnInitialize_Implementation()
{
	CustomData = CastChecked<UDesertClawUltimateAbilityData>( Data );

	PassiveAbility = CastChecked<UDesertClawPassiveAbility>( Character->GetAbility( EMobaAbilitySlot::Passive ) );

	SpawnDecal();
}

void UDesertClawUltimateAbility::OnTick_Implementation( float dt )
{
	//kPRINT_TICK( "yel" );

	if ( IsActive )
	{
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
			UltimateActor->SetActorLocation( result.Location );
		}
		
		//  startup timer
		if ( ( StartupTime -= dt ) <= 0.0f )
		{
			EndStartup();
			return;
		}
	}
}

void UDesertClawUltimateAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{
	BeginStartup();
}

void UDesertClawUltimateAbility::OnStop_Implementation( FMobaAbilityRunContext context )
{
	EndStartup();
}

void UDesertClawUltimateAbility::BeginStartup()
{	
	IsActive = true;

	StartupTime = CustomData->StartupTime;

	//  show in game
	UltimateActor->SetActorHiddenInGame( false );

	kPRINT( "Ultimate: Begin Startup" );
}

void UDesertClawUltimateAbility::EndStartup()
{
	IsActive = false;

	//  hide in game
	UltimateActor->SetActorHiddenInGame( true );

	//  schedule refill
	RefillGaugeAfterDelay();

	//  reset active slot
	Character->ResetAbilitySlot( Data->ActiveOverrideSlot );

	kPRINT( "Ultimate: End Startup" );
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
	UltimateActor = GetWorld()->SpawnActor<ADesertClawUltimateDecal>( 
		CustomData->DecalActorClass,
		FVector( 0.0f, 0.0f, 0.0f ),
		FRotator( 0.0f, 0.0f, 0.0f )
	);

	//  set scale
	FVector scale = GetDecalScaleFromSize( 
		CustomData->DecalRadius, 
		CustomData->DecalHeight 
	);
	UltimateActor->SetActorScale3D( scale );

	//  hide in game
	UltimateActor->SetActorHiddenInGame( true );
}

FVector UDesertClawUltimateAbility::GetDecalScaleFromSize( float radius, float height )
{
	/*
	 *  For some reasons, the decal is 90° pitch-rotated so:
	 *  - YZ is Radius
	 *  - X is height
	 */
	FVector decal_size = UltimateActor->GetDecalComponent()->DecalSize;
	return FVector(
		height / decal_size.X,
		radius / decal_size.Y,
		radius / decal_size.Y
	);
}

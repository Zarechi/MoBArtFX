#include "Characters/DesertClaw/DesertClawAutoAttackAbility.h"
#include "Defines.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"

void UDesertClawAutoAttackAbility::OnInitialize_Implementation()
{
	PassiveAbility = CastChecked<UMobaAbility>( Character->GetAbility( EMobaAbilitySlot::Passive ) );
	CustomData = CastChecked<UDesertClawAutoAttackAbilityData>( Data );
}

void UDesertClawAutoAttackAbility::OnTick_Implementation( float dt )
{
	if ( !IsActive ) return;
	
	//  TODO: passive cost
	//PassiveAbility->SetCooldown( 1.0f );

	UWorld* world = GetWorld();
	auto controller = CastChecked<APC_MoBArtFX>( Character->GetController() );

	//  query params
	FCollisionQueryParams query_params {};
	query_params.TraceTag = FName( "Ability" );
	query_params.AddIgnoredActor( Character );

	//  response params
	FCollisionResponseParams response_params {};

	//  line trace 
	FHitResult result;
	if ( controller->CameraTraceSingleByChannel(
		    result,
		    CustomData->Range,
			CustomData->CollisionChannel,
			query_params,
			response_params
		) )
	{
		AActor* actor = result.GetActor();
		actor->TakeDamage( CustomData->Damage * dt, FDamageEvent {}, Character->GetController(), Character );
		kPRINT_TICK( result.GetActor()->GetName() );
	}

	kDEBUG_LINE_TRACE( world, result );
}

void UDesertClawAutoAttackAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{}

void UDesertClawAutoAttackAbility::OnStop_Implementation( FMobaAbilityRunContext context )
{}

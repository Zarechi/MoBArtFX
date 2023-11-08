#include "Characters/DesertClaw/DesertClawAutoAttackAbility.h"
#include "Engine/DamageEvents.h"
#include "Defines.h"

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

	auto world = GetWorld();

	//  setup line segment
	FVector start = Character->GetActorLocation();
	FVector dir = Character->GetActorForwardVector();
	FVector end = start + dir * CustomData->Range;

	//  setup params
	FCollisionQueryParams query_params {};
	query_params.TraceTag = FName( "Ability" );
	query_params.AddIgnoredActor( Character );
	FCollisionResponseParams response_params {};

	//  line trace 
	FHitResult result;
	if ( world->LineTraceSingleByChannel(
			result,
			start,
			end,
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

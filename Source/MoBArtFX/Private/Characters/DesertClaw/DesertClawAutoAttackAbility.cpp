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
	TArray<AActor*> ignored_actors;
	ignored_actors.Add( Character );

	//  get trace locations
	FVector start, end;
	controller->GetCameraTraceBounds( start, end, CustomData->Range );

	//  sphere trace 
	FHitResult result;
	UKismetSystemLibrary::SphereTraceSingleForObjects( 
		Character,
		start, 
		end, 
		CustomData->Radius,
		CustomData->QueryObjectTypes,
		false,
		ignored_actors,
		CustomData->DrawDebugType,
		result,
		true
	);

	//  check result
	if ( result.bBlockingHit )
	{
		AActor* actor = result.GetActor();

		//  inflict damage
		actor->TakeDamage( 
			CustomData->Damage * dt, 
			FDamageEvent {}, 
			Character->GetController(), 
			Character 
		);

		kPRINT_TICK( result.GetActor()->GetName() );
	}
}

void UDesertClawAutoAttackAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{}

void UDesertClawAutoAttackAbility::OnStop_Implementation( FMobaAbilityRunContext context )
{}

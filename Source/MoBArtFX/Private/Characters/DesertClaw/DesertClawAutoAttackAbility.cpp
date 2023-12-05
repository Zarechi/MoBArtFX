#include "Characters/DesertClaw/DesertClawAutoAttackAbility.h"
#include "Defines.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"
#include "MobaGameplayStatics.h"

void UDesertClawAutoAttackAbility::OnInitialize_Implementation()
{
	PassiveAbility = CastChecked<UDesertClawPassiveAbility>( Character->GetAbility( EMobaAbilitySlot::Passive ) );
	CustomData = CastChecked<UDesertClawAutoAttackAbilityData>( Data );
}

void UDesertClawAutoAttackAbility::OnTick_Implementation( float dt )
{
	if ( !IsActive ) return;
	
	//  auto-disable when running out of sand
	if ( PassiveAbility->GetSandPercent() <= 0.01f )
	{
		IsActive = false;
		return;
	}
	
	//  reset passive cooldown
	PassiveAbility->ResetCooldown();

	//  check passive cost
	float sand_cost = CustomData->SandCost * dt;
	if ( !PassiveAbility->CanAffordSand( sand_cost ) ) return;
	PassiveAbility->AddSandPercent( -sand_cost );

	//  get references
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
	UKismetSystemLibrary::SphereTraceSingle( 
		Character,
		start, 
		end, 
		CustomData->Radius,
		CustomData->TraceType,
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
		UMobaGameplayStatics::ApplyMobaDamage(
			actor,
			CustomData->Damage * dt,
			Character,
			Character
		);

		//kPRINT_TICK( result.GetActor()->GetName() );
	}
}

void UDesertClawAutoAttackAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{}

void UDesertClawAutoAttackAbility::OnStop_Implementation( FMobaAbilityRunContext context )
{}

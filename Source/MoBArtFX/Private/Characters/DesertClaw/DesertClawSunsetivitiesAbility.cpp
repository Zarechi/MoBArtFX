#include "Characters/DesertClaw/DesertClawSunsetivitiesAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

void UDesertClawSunsetivitiesAbility::OnInitialize_Implementation()
{
	PassiveAbility = CastChecked<UDesertClawPassiveAbility>( Character->GetAbility( EMobaAbilitySlot::Passive ) );
	CustomData = CastChecked<UDesertClawSunsetivitiesAbilityData>( Data );
}

void UDesertClawSunsetivitiesAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{
	ADesertClawPlayerController* controller = Character->GetPlayerController();

	//  pay sand cost
	PassiveAbility->AddSandPercent( -CustomData->SandCost );

	//  get spawn location
	FVector start, end;
	controller->GetCameraTraceBounds( start, end, CustomData->ThrowDistance );

	//  spawn grenade
	ADesertClawSunsetivitiesGrenade* grenade = GetWorld()->SpawnActor<ADesertClawSunsetivitiesGrenade>( 
		CustomData->GrenadeActorClass, 
		end, 
		FRotator { 
			0.0f, 
			Character->GetControlRotation().Yaw, 
			90.0f 
		} 
	);
	grenade->SetupData( CustomData );

	//  get impulse
	FVector impulse = end - start;
	impulse += CustomData->ThrowImpulseOffset;
	impulse.Normalize();
	impulse *= CustomData->ThrowImpulseForce;

	//  apply impulse
	grenade->Mesh->AddImpulse( impulse );
}

bool UDesertClawSunsetivitiesAbility::CanRun_Implementation( FMobaAbilityRunContext context )
{
	if ( !PassiveAbility->CanAffordSand( CustomData->SandCost ) ) return false;

	return true;
}

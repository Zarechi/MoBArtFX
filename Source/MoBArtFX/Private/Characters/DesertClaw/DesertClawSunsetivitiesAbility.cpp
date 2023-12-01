#include "Characters/DesertClaw/DesertClawSunsetivitiesAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

void UDesertClawSunsetivitiesAbility::OnInitialize_Implementation()
{
	CustomData = CastChecked<UDesertClawSunsetivitiesAbilityData>( Data );
}

void UDesertClawSunsetivitiesAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{
	ADesertClawPlayerController* controller = Character->GetPlayerController();

	//  get spawn location
	FVector start, end;
	controller->GetCameraTraceBounds( start, end, CustomData->ThrowDistance );

	//  spawn grenade
	ADesertClawSunsetivitiesGrenade* grenade = GetWorld()->SpawnActor<ADesertClawSunsetivitiesGrenade>( 
		CustomData->GrenadeActorClass, 
		end, 
		FRotator { 
			0.0f, 
			Character->GetActorRotation().Yaw, 
			0.0f 
		} 
	);

	//  get impulse
	FVector impulse = end - start;
	impulse += CustomData->ThrowImpulseOffset;
	impulse.Normalize();
	impulse *= CustomData->ThrowImpulseForce;

	//  apply impulse
	grenade->Mesh->AddImpulse( impulse );
}

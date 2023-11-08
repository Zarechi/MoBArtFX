#include "Characters/DesertClaw/MobaAbility.h"

#include "Defines.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

void UMobaAbility::Setup( ADesertClawCharacter* character, UMobaAbilityData* data, EMobaAbilitySlot slot )
{
	Character = character;
	Data = data;
	Mode = data->Mode;
	Slot = slot;
}

void UMobaAbility::Initialize()
{
	//  custom initialize
	OnInitialize();
}

bool UMobaAbility::Run( FMobaAbilityRunContext context )
{
	if ( IsOnCooldown() )
	{
		kPRINT_WARNING( "Ability: " + Data->Name + " is on cooldown (" + FString::SanitizeFloat( Cooldown ) + "s)" );
		return false;
	}

	//  toggle on/off mode
	if ( Mode == EMobaAbilityMode::OnOff )
	{
		if ( context.IsStartInput )
		{
			IsActive = !IsActive;
		}
		else
		{
			IsActive = false;
		}

		//  custom callback
		if ( IsActive )
		{
			//  reset cooldown
			Cooldown = Data->ToggleCooldown;

			//  custom callback
			OnRun( context );
		}
		else
		{
			//  reset cooldown
			ResetCooldown();

			//  custom callback
			OnStop( context );
		}

		//  add temporaly additional slot
		if ( Data->UseActiveOverrideSlot )
		{
			if ( IsActive )
			{
				Character->OverrideAbilitySlot( Data->ActiveOverrideSlot, this );
			}
			else
			{
				Character->ResetAbilitySlot( Data->ActiveOverrideSlot );
			}
		}
	}
	else
	{
		//  reset cooldown
		ResetCooldown();

		//  custom callback
		OnRun( context );
	}

	return true;
}

void UMobaAbility::Tick( float dt )
{
	//  decrease cooldown
	if ( Cooldown > 0.0f )
	{
		Cooldown = FMath::Max( 0.0f, Cooldown - dt );
	}

	//  custom callback
	OnTick( dt );

	//kPRINT_TICK( "aiblity tick!" );
}

void UMobaAbility::OnInitialize_Implementation() {}

void UMobaAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{
	kPRINT( "Running '" + Data->Name + "' (IsActive=" + ( IsActive ? "True" : "False" ) + ")" );
}

void UMobaAbility::OnStop_Implementation( FMobaAbilityRunContext context )
{
	kPRINT( "Stopping '" + Data->Name + "' (IsActive=" + ( IsActive ? "True" : "False" ) + ")" );
}

void UMobaAbility::OnTick_Implementation( float dt ) {}

UWorld* UMobaAbility::GetWorld() const
{
	if ( Character == nullptr ) return nullptr;
	return Character->GetWorld();
}

void UMobaAbility::ResetCooldown()
{
	Cooldown = Data->Cooldown;
}

FString UMobaAbility::GetName() const
{
	if ( Data == nullptr ) return FString( "MobaAbility(NoData)" );
	return Data->Name;
}

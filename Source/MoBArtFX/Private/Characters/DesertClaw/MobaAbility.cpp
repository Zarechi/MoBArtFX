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
	if ( Mode == EMobaAbilityMode::ON_OFF )
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
			Cooldown = Data->Cooldown;

			//  custom callback
			OnStop( context );
		}

		//  add temporaly additional slot
		if ( Data->UseActiveOverrideSlot )
		{
			if ( IsActive )
			{
				//  TODO:
				//Character->OverrideAbilitySlot( Data->ActiveOverrideSlot, this );
			}
			else
			{
				//  TODO:
				//Character->ResetAbilitySlot( Data->ActiveOverrideSlot );
			}
		}
	}
	else
	{
		//  reset cooldown
		Cooldown = Data->Cooldown;

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

void UMobaAbility::OnRun_Implementation( FMobaAbilityRunContext context )
{
	kPRINT( "Running '" + Data->Name + "' (IsActive=" + ( IsActive ? "True" : "False" ) + ")" );
}

UWorld* UMobaAbility::GetWorld() const
{
	if ( Character == nullptr ) return nullptr;
	return Character->GetWorld();
}

FString UMobaAbility::GetName() const
{
	if ( Data == nullptr ) return FString( "MobaAbility(NoData)" );
	return Data->Name;
}

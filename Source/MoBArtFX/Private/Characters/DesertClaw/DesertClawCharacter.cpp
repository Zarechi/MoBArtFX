#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "Defines.h"

void ADesertClawCharacter::BeginPlay()
{
	Super::BeginPlay();

	//  cast player infos
	Data = CastChecked<UDesertClawPlayerInfos>( GetPlayerDatas() );

	//  init abilities
	InitializeAbilities();
}

void ADesertClawCharacter::Tick( float dt )
{
	kPRINT_TICK( FString::SanitizeFloat( dt ) );

	//  tick abilities
	for ( auto& pair : Abilities )
	{
		auto ability = pair.Value;
		ability->Tick( dt );
	}
}

void ADesertClawCharacter::InitializeAbilities()
{
	check( Data != nullptr );

	//  create
	for ( auto& pair : Data->Abilities )
	{
		CreateAbility( pair.Key, pair.Value );
	}

	//  setup hud
	//  TODO:
	/*if ( PlayerController )
	{
		PlayerController->SetupHUD();
	}*/

	//  init
	for ( auto& pair : Abilities )
	{
		auto ability = pair.Value;
		ability->Initialize();
		kPRINT( "Initializing ability '" + ability->GetName() + "'" );
	}
}

UMobaAbility* ADesertClawCharacter::CreateAbility( EMobaAbilitySlot slot, UMobaAbilityData* data )
{
	if ( data == nullptr || data->Class == nullptr ) return nullptr;

	//  create ability
	auto ability = NewObject<UMobaAbility>( this, data->Class, FName( "MobaAbility('" + data->Name + "')" ) );
	ability->Setup( this, data, slot );

	//  bind ability to controller
	//  TODO:
	/*if ( PlayerController )
	{
		PlayerController->BindAbility( ability );
	}*/

	//  register
	Abilities.Add( slot, ability );
	InputsToAbilities.Add( slot, ability );

	return ability;
}

void ADesertClawCharacter::Death_Implementation()
{
	kPRINT( "DESERT CLAW IS DEAD!" );
}

void ADesertClawCharacter::AutoAttack_Implementation()
{
	kPRINT( "AUTO ATTACK!" );
}

void ADesertClawCharacter::Reload_Implementation()
{
	kPRINT( "RELOAD !" );
}

void ADesertClawCharacter::Spell_01_Implementation()
{
	kPRINT( "SPELL 01!" );
}

void ADesertClawCharacter::Spell_02_Implementation()
{
	kPRINT( "SPELL 02!" );
}

void ADesertClawCharacter::Ultimate_Implementation()
{
	kPRINT( "ULTIMATE!" );
}

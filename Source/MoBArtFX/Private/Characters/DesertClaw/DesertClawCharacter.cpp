#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "Defines.h"

void ADesertClawCharacter::BeginPlay()
{
	Super::BeginPlay();

	//  cast player controller
	PlayerController = CastChecked<ADesertClawPlayerController>( GetController() );

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
	if ( PlayerController )
	{
		PlayerController->BindAbility( ability );
	}

	//  register
	Abilities.Add( slot, ability );
	InputsToAbilities.Add( slot, ability );

	return ability;
}

UMobaAbility* ADesertClawCharacter::GetAbility( EMobaAbilitySlot slot )
{
	if ( auto itr = Abilities.Find( slot ) ) return *itr;
	return nullptr;
}

void ADesertClawCharacter::OverrideAbilitySlot( EMobaAbilitySlot slot, UMobaAbility* ability )
{
	InputsToAbilities.Add( slot, ability );
}

void ADesertClawCharacter::ResetAbilitySlot( EMobaAbilitySlot slot )
{
	UMobaAbility* ability = GetAbility( slot );
	if ( !IsValid( ability ) )
	{
		InputsToAbilities.Remove( slot );
		kPRINT_WARNING( "Character: couldn't reset ability input slot of '" + UEnum::GetValueAsString<EMobaAbilitySlot>( slot ) + "', original ability is NOT valid!" );
		return;
	}

	InputsToAbilities.Add( slot, ability );
}

void ADesertClawCharacter::ProcessAbility( EMobaAbilitySlot slot, bool is_started )
{
	//kPRINT( "Process Ability: " + UEnum::GetValueAsString<EMobaAbilitySlot>( slot ) );

	//  find ability at input slot
	auto itr = InputsToAbilities.Find( slot );
	if ( !itr )
	{
		kPRINT_WARNING( "Character: no Ability found on Input slot '" + UEnum::GetValueAsString<EMobaAbilitySlot>( slot ) + "'" );
		return;
	}

	//  get ability and its data
	UMobaAbility* ability = *itr;
	UMobaAbilityData* data = ability->GetData();

	//  ignore end input if not a holded ability
	if ( !is_started && !data->IsHolded ) return;

	//  construct context
	FMobaAbilityRunContext context {};
	context.IsOverridenSlot = slot != ability->Slot;
	context.IsStartInput = is_started;

	//  run ability
	ability->Run( context );
}

void ADesertClawCharacter::Death_Implementation()
{
	kPRINT( "DESERT CLAW IS DEAD!" );
}

/*
void ADesertClawCharacter::AutoAttack_Implementation()
{
	ProcessAbility( EMobaAbilitySlot::AutoAttack, true );
	kPRINT( "AUTO ATTACK!" );
}

void ADesertClawCharacter::Reload_Implementation()
{
	kPRINT( "RELOAD !" );
}

void ADesertClawCharacter::Spell_01_Implementation()
{
	ProcessAbility( EMobaAbilitySlot::First, true );
	kPRINT( "SPELL 01!" );
}

void ADesertClawCharacter::Spell_02_Implementation()
{
	ProcessAbility( EMobaAbilitySlot::Second, true );
	kPRINT( "SPELL 02!" );
}

void ADesertClawCharacter::Ultimate_Implementation()
{
	ProcessAbility( EMobaAbilitySlot::Ultimate, true );
	kPRINT( "ULTIMATE!" );
}
*/
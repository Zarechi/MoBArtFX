#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "Defines.h"

void ADesertClawCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

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
		//CreateAbility( pair.Key, pair.Value );
	}

	//  setup hud
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

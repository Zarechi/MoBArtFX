#include "Characters/DesertClaw/DesertClawPlayerController.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"

#include "Defines.h"

void ADesertClawPlayerController::BindAbilitiesActions() 
{
	//  cast character for further use..
	Character = CastChecked<ADesertClawCharacter>( GetPawn() );

	/*
	 *  Actions of this character are dynamically binded because some
	 *  abilities may needs of certain input state depending on their 
	 *  Data Asset and their design.
	 * 
	 *  See ADesertClawPlayerController::BindAbility
	 */
	kPRINT( "Bind Abilities Actions" );
}

void ADesertClawPlayerController::BindAbility( UMobaAbility* ability )
{
	if ( EnhancedInputComponent == nullptr ) return;

	//  get input action from slot
	UInputAction* action = nullptr;
	switch ( ability->Slot )
	{
		case EMobaAbilitySlot::First:
			action = Spell01_Action;
			break;
		case EMobaAbilitySlot::Second:
			action = Spell02_Action;
			break;
		case EMobaAbilitySlot::Ultimate:
			action = UltimateAction;
			break;
		case EMobaAbilitySlot::AutoAttack:
			action = AutoAttackAction;
			break;
		default:
			return;
	}

	//  bind start input
	EnhancedInputComponent->BindAction(
		action,
		ETriggerEvent::Started,
		Character,
		&ADesertClawCharacter::ProcessAbility,
		ability->Slot,
		true
	);

	if ( ability->GetData()->IsHolded )
	{
		//  bind end input
		EnhancedInputComponent->BindAction(
			action,
			ETriggerEvent::Completed,
			Character,
			&ADesertClawCharacter::ProcessAbility,
			ability->Slot,
			false
		);
	}

	kPRINT( "Bind Ability: " + ability->GetName() );
}

#include "Characters/DesertClaw/DesertClawPassiveAbility.h"
#include "Characters/DesertClaw/DesertClawCharacter.h"
#include "Defines.h"

void UDesertClawPassiveAbility::OnInitialize_Implementation()
{
	CustomData = CastChecked<UDesertClawPassiveAbilityData>( Data );

	UpdateSandHUD();
}

void UDesertClawPassiveAbility::OnTick_Implementation( float dt )
{
	if ( !IsOnCooldown() ) 
	{
		AddSandPercent( CustomData->SandGainRate * dt );
		kPRINT_TICK( "Passive Gain: " + FString::SanitizeFloat( GetSandPercent() ) );
	}
}

void UDesertClawPassiveAbility::AddSandPercent( float amount )
{
	float old_percent = SandPercent;
	SandPercent = FMath::Clamp( SandPercent + amount, 0.0f, 1.0f );

	//  reflect changes on data (e.g. HUD)
	Character->GetPlayerDatas()->CurrentAmmo = SandPercent * 100;

	//  update on change
	if ( old_percent != SandPercent )
	{
		UpdateSandHUD();
	}

	//  reset cooldown
	if ( amount < 0.0f )
	{
		SetCooldown( Data->Cooldown );
		kPRINT_TICK( "Passive on Cooldown" );
	}
}

bool UDesertClawPassiveAbility::CanAffordSand( float amount )
{
	return SandPercent >= amount;
}

void UDesertClawPassiveAbility::UpdateSandHUD()
{
	/*if ( ChampionWidget == nullptr )
	{
		ChampionWidget = CastChecked<UMobaDesertClawHUDWidget>( Character->GetPlayerController()->GetHUD()->GetWidget()->GetChampionWidget() );
		ensureAlwaysMsgf( ChampionWidget != nullptr, TEXT( "DesertClawPassive: ChampionWidget is NOT valid!" ) );
	}
	
	ChampionWidget->UpdateSand( SandPercent );*/
}

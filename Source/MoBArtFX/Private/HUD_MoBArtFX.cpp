#include "HUD_MoBArtFX.h"

#include "Defines.h"
#include "PS_MoBArtFX.h"
#include "BaseCharacter.h"
#include "Blueprint/UserWidget.h"

void AHUD_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	if (ViewportInstance)
		return;

	kPRINT_ERROR("[AHUD_MoBArtFX]");
	auto controller = GetOwningPlayerController();
	if (!controller) {
		kPRINT_ERROR("[AHUD_MoBArtFX::BeginPlay] Moba HUD couldn't get the controller!");
		return;
	}

	auto pawn = controller->GetPawn();
	if (!pawn)
	{
		kPRINT_ERROR("[AHUD_MoBArtFX::BeginPlay] Moba HUD couldn't get the pawn!");
		return;
	}

	auto character = Cast<ABaseCharacter>( controller->GetPawn() );
	if ( !character )
	{
		kPRINT_ERROR( "[AHUD_MoBArtFX::BeginPlay] Moba HUD couldn't cast the controlled pawn to ABaseCharacter!" );
		return;
	}

	auto data = character->GetPlayerDatas(); // Ici le client n'arrive pas à faire ça
	if (!data) 
	{
		kPRINT_ERROR("[AHUD_MoBArtFX::BeginPlay] Moba HUD couldn't get the player data!");
		return;
	}
	ViewportInstance = CreateWidget<>( controller, data->ViewportClass, FName( "Viewport" ) );
	ViewportInstance->AddToPlayerScreen();
}

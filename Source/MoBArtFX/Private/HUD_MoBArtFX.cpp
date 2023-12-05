#include "HUD_MoBArtFX.h"

#include "Defines.h"
#include "PS_MoBArtFX.h"
#include "BaseCharacter.h"
#include "Blueprint/UserWidget.h"

void AHUD_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	auto controller = GetOwningPlayerController();
	auto character = Cast<ABaseCharacter>( controller->GetPawn() );
	if ( !character )
	{
		kPRINT_ERROR( "Moba HUD couldn't cast the controlled pawn to ABaseCharacter!" );
		return;
	}

	auto data = character->GetPlayerDatas();
	ViewportInstance = CreateWidget<>( controller, data->ViewportClass, FName( "Viewport" ) );
	ViewportInstance->AddToPlayerScreen();

	SetViewportPlayerDatas();
}

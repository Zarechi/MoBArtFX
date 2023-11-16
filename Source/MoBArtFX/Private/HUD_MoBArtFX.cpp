#include "HUD_MoBArtFX.h"

#include "PS_MoBArtFX.h"
#include "BaseCharacter.h"
#include "Blueprint/UserWidget.h"

void AHUD_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	auto controller = GetOwningPlayerController();
	auto character = CastChecked<ABaseCharacter>( controller->GetPawn() );
	auto data = character->GetPlayerDatas();
	
	ViewportInstance = CreateWidget<>( controller, data->ViewportClass, FName( "Viewport" ) );
	ViewportInstance->AddToPlayerScreen();
}

#include "Characters/Cainer/PC_Cainer.h"

void APC_Cainer::BindAbilitiesActions()
{
	Super::BindAbilitiesActions();

	EnhancedInputComponent->BindAction(PingMonstroAction, ETriggerEvent::Triggered, this, &APC_Cainer::PingMonstro);
}

void APC_Cainer::PingMonstro(const FInputActionValue& Value)
{
	if (PlayerCharacter->IsDead()) return;

	Cast<ACainerCharacter>(PlayerCharacter)->PingMonstro();
}

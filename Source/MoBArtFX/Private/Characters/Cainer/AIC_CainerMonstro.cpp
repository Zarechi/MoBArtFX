#include "Characters/Cainer/AIC_CainerMonstro.h"


bool AAIC_CainerMonstro::SetDestination(FVector destination)
{
	EPathFollowingRequestResult::Type result;
	result = MoveToLocation(destination);

	if (result == EPathFollowingRequestResult::Type::RequestSuccessful) return true;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, "Monstro can't reach this destination !");
	return false;
}

bool AAIC_CainerMonstro::IsMoving()
{
	return GetMoveStatus() == EPathFollowingStatus::Moving;
}

void AAIC_CainerMonstro::Stop()
{
	StopMovement();
}

void AAIC_CainerMonstro::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
}

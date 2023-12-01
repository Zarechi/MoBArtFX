#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_MoBArtFX.generated.h"

UCLASS()
class MOBARTFX_API AGM_MoBArtFX : public AGameMode
{
	GENERATED_BODY()

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};

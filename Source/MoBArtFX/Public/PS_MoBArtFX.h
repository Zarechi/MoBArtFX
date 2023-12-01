#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <PlayerInfos.h>
#include "PS_MoBArtFX.generated.h"

UCLASS()
class MOBARTFX_API APS_MoBArtFX : public APlayerState
{
	GENERATED_BODY()


public:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category="PlayerDatas", meta=(AllowedClasses="UPlayerInfos"))
	TSoftObjectPtr<UPlayerInfos> PlayerDatas_Asset;
	UPROPERTY(BlueprintReadOnly, Category="PlayerDatas", meta=(EditCondition="false"))
	TObjectPtr<UPlayerInfos> PlayerDatas;

};

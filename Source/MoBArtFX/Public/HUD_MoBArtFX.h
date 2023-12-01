#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfos.h"
#include "HUD_MoBArtFX.generated.h"

/** HUD Interface */

UINTERFACE(MinimalAPI, Blueprintable)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};
class IHUDInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "HUD" )
	void Cooldown( double time, int type );
};

/** HUD Class */
UCLASS()
class MOBARTFX_API AHUD_MoBArtFX : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "HUD" )
	void Cooldown( float time, EMobaAbilitySlot type );
	
	UPROPERTY(BlueprintReadOnly, Category = Viewport)
	TObjectPtr<UUserWidget> ViewportInstance;
};

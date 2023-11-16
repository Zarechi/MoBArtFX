#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
	void Cooldown(double _CooldownTime, int SpellNum = -1);
};

/** HUD Class */

UCLASS()
class MOBARTFX_API AHUD_MoBArtFX : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = Viewport)
	TObjectPtr<UUserWidget> ViewportInstance;
};

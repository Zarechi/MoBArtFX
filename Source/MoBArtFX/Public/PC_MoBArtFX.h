#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUD_MoBArtFX.h"
#include "PC_MoBArtFX.generated.h"

class UInputComponent;
class UInputMappingContext;

UCLASS()
class MOBARTFX_API APC_MoBArtFX : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void BindActions();
	virtual void BindMovementActions();
	virtual void BindAbilitiesActions();

	UFUNCTION( BlueprintCallable )
	void ApplySpellCooldownOnHUD( float time, EMobaAbilitySlot type );

	/*
	 *  Performs a Line Trace Single by Channel using the camera location 
	 *  and direction.
	 * 
	 *  Internally uses GetCameraTraceBounds
	 */
	bool CameraTraceSingleByChannel( 
		FHitResult& out, 
		float distance, 
		ECollisionChannel collision_channel, 
		const FCollisionQueryParams& params,
		const FCollisionResponseParams& response_param 
	);
	/*
	 *  Returns Line Trace Start and End locations using the Camera
	 */
	UFUNCTION( BlueprintCallable )
	void GetCameraTraceBounds( FVector& start, FVector& end, float distance );

	UPROPERTY(BlueprintReadOnly, Category=Character)
	TObjectPtr<ABaseCharacter> PlayerCharacter = nullptr;
	
	/* MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMC_DefaultPlayer;

	/** InputActions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AutoAttackAction;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Spell01_Action;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Spell02_Action;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UltimateAction;

protected:
	UEnhancedInputComponent* EnhancedInputComponent;

	/* InputEvents */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void AutoAttack(const FInputActionValue& Value);
	void Spell01(const FInputActionValue& Value);
	void Spell02(const FInputActionValue& Value);
	void Ultimate(const FInputActionValue& Value);

private:
	AHUD_MoBArtFX* HUD;
};

#include "PC_MoBArtFX.h"
#include "HUD_MoBArtFX.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Defines.h"

void APC_MoBArtFX::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	
	//  cast base character
	PlayerCharacter = CastChecked<ABaseCharacter>( GetPawn() );

	//  cast HUD
	HUD = CastChecked<AHUD_MoBArtFX>( GetHUD() );
	
	//  setup mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_DefaultPlayer, 0);
	}
	
	//  set up action bindings
	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>( InputComponent );
	BindActions();
}

void APC_MoBArtFX::BindActions()
{
	BindMovementActions();
	BindAbilitiesActions();
}

void APC_MoBArtFX::BindMovementActions()
{
	//Jumping
	EnhancedInputComponent->BindAction( JumpAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Jump );
	EnhancedInputComponent->BindAction( JumpAction, ETriggerEvent::Completed, this, &APC_MoBArtFX::StopJump );

	//Moving
	EnhancedInputComponent->BindAction( MoveAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Move );

	//Looking
	EnhancedInputComponent->BindAction( LookAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Look );
}

void APC_MoBArtFX::BindAbilitiesActions()
{
	//Attacks
	EnhancedInputComponent->BindAction( AutoAttackAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::AutoAttack );
	EnhancedInputComponent->BindAction( Spell01_Action, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Spell01 );
	EnhancedInputComponent->BindAction( Spell02_Action, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Spell02 );
	EnhancedInputComponent->BindAction( UltimateAction, ETriggerEvent::Triggered, this, &APC_MoBArtFX::Ultimate );
}

void APC_MoBArtFX::ApplySpellCooldownOnHUD( float time, EMobaSpellType type )
{
	if ( !IsValid( HUD ) )
	{
		kERROR_LOG_ARGS( "ApplySpellCooldown: HUDInterface is NOT valid!" );
		return;
	}

	HUD->Cooldown( time, type );
}

bool APC_MoBArtFX::CameraTraceSingleByChannel( FHitResult& out, float distance, ECollisionChannel collision_channel, const FCollisionQueryParams& params, const FCollisionResponseParams& response_param )
{
	FVector trace_start, trace_end;
	GetCameraTraceBounds( trace_start, trace_end, distance );

	return GetWorld()->LineTraceSingleByChannel(
		out,
		trace_start,
		trace_end,
		collision_channel,
		params,
		response_param
	);
}

void APC_MoBArtFX::GetCameraTraceBounds( FVector& start, FVector& end, float distance )
{
	start = PlayerCameraManager->GetCameraLocation();
	end = start + PlayerCameraManager->GetActorForwardVector() * distance;
}

void APC_MoBArtFX::Move(const FInputActionValue& Value)
{
	FRotator rotation = GetControlRotation();
	rotation.Pitch = 0.0f;

	// Forward Movement
	PlayerCharacter->AddMovementInput(UKismetMathLibrary::GetForwardVector(rotation), Value.Get<FVector2D>().X);
	
	// Right Movement
	PlayerCharacter->AddMovementInput(UKismetMathLibrary::GetRightVector(rotation), Value.Get<FVector2D>().Y);
}

void APC_MoBArtFX::Look(const FInputActionValue& Value)
{
	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(Value.Get<FVector2D>().Y * -1);
}

void APC_MoBArtFX::Jump(const FInputActionValue& Value)
{
	PlayerCharacter->Jump();
}

void APC_MoBArtFX::StopJump(const FInputActionValue& Value)
{
	PlayerCharacter->StopJumping();
}

void APC_MoBArtFX::AutoAttack(const FInputActionValue& Value)
{
	PlayerCharacter->AutoAttack();
}

void APC_MoBArtFX::Spell01(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_01"));
	PlayerCharacter->Spell_01();
}

void APC_MoBArtFX::Spell02(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Launch Spell_02"));
	PlayerCharacter->Spell_02();
}

void APC_MoBArtFX::Ultimate(const FInputActionValue& Value)
{
	PlayerCharacter->Ultimate();
}

#include "BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Defines.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//  get player state
	PlayerState = GetPlayerState<APS_MoBArtFX>();
	
	//  setup data
	SetPlayerDatas( GetPlayerDatas() );
}

void ABaseCharacter::SetPlayerDatas( UPlayerInfos* data )
{
	PlayerState->PlayerDatas = data;

	if ( data == nullptr )
	{
		kPRINT_ERROR( "A BaseCharacter doesn't have a PlayerInfos data asset!" );
		return;
	}

	SetupData( data );
}

UPlayerInfos* ABaseCharacter::GetPlayerDatas()
{
	//  ensure PlayerState has been retrieved
	if ( !HasActorBegunPlay() )
	{
		DispatchBeginPlay();
	}

	//  get player state
	if ( IsValid( PlayerState ) ) return PlayerState->PlayerDatas;

	//  get debug data
	if ( DebugPlayerInfos )
	{
		return DebugPlayerInfos;
	}

	UE_LOG( LogTemp, Error, TEXT( "Can't find PlayerDatas" ) );
	return nullptr;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::SetupData( UPlayerInfos* data )
{
	auto movement = GetCharacterMovement();
	if ( ensureMsgf( IsValid( movement ), TEXT( "Movement Component couldn't be retrieved!" ) ) )
	{
		movement->MaxWalkSpeed = data->MaxWalkSpeed;
		movement->JumpZVelocity = data->JumpVelocity;
		movement->AirControl = data->AirControl;
	}

	kLOG_ARGS( TEXT( "Character '%s' data has been setup" ), *data->Name );
}

void ABaseCharacter::AutoAttack_Implementation()
{	
	if(GetPlayerDatas()->CurrentAmmo <= 0)
	{
		GetPlayerDatas()->CurrentAmmo = 0;
		Reload();
	}
}

void ABaseCharacter::Reload_Implementation()
{
	GetPlayerDatas()->CurrentAmmo = GetPlayerDatas()->MaxAmmo;
}

void ABaseCharacter::Spell_01_Implementation() {}

void ABaseCharacter::Spell_02_Implementation() {}

void ABaseCharacter::Ultimate_Implementation() {}

void ABaseCharacter::Death_Implementation() {}
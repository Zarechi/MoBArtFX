#include "BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "PC_MoBArtFX.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Defines.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

float ABaseCharacter::TakeDamage(
	const float Damage,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	auto data = GetPlayerDatas();
	if ( !IsValid( data ) ) return 0.0f;
	if ( data->CurrentHealth == 0.0f ) return 0.0f;

	//  mitigate damage
	float took_damage = Super::TakeDamage( Damage, DamageEvent, EventInstigator, DamageCauser );
	took_damage = MitigateDamage( took_damage, DamageCauser );

	//  apply damage
	data->CurrentHealth = FMath::Max( 0.0f, data->CurrentHealth - took_damage );

	//  check death
	if ( data->CurrentHealth == 0.0f )
	{
		Death();
	}

	return took_damage;
}

float ABaseCharacter::MitigateDamage_Implementation( float damage, AActor* causer )
{
	return damage;
}

void ABaseCharacter::ApplySpellCooldown( float time, EMobaSpellType type )
{
	SpellCooldowns.Add( type, time );

	if ( IsValid( CustomPlayerController ) )
	{
		CustomPlayerController->ApplySpellCooldownOnHUD( time, type );
	}

	auto data = GetPlayerDatas();
	if ( IsValid( data ) )
	{
		auto type_name = StaticEnum<EMobaSpellType>()->GetValueAsString( type );
		kLOG_ARGS( "%s: %s is on cooldown for %ds!", *data->Name, *type_name, time );
	}
}

bool ABaseCharacter::IsSpellOnCooldown( EMobaSpellType type )
{
	auto itr = SpellCooldowns.Find( type );
	if ( itr == nullptr ) return false;

	return *itr > 0.0f;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//  get player state
	CustomPlayerState = GetPlayerState<APS_MoBArtFX>();
	if ( CustomPlayerState == nullptr && GetController<APC_MoBArtFX>() )
	{
		kERROR_LOG_ARGS( "A Player-Controlled Character doesn't have a valid Player State!" );
	}
	
	//  setup data
	SetPlayerDatas( GetPlayerDatas() );
}

void ABaseCharacter::SetPlayerDatas( UPlayerInfos* data )
{
	if ( !IsValid( CustomPlayerState ) ) return;

	CustomPlayerState->PlayerDatas = data;

	if ( data == nullptr )
	{
		kPRINT_ERROR( "A Character doesn't have a PlayerInfos data asset!" );
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
	if ( IsValid( CustomPlayerState ) ) return CustomPlayerState->PlayerDatas;

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

	kLOG_ARGS( "Character '%s' data has been setup", *data->Name );
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

void ABaseCharacter::Death_Implementation() 
{
	auto data = GetPlayerDatas();
	if ( !IsValid( data ) ) return;

	kPRINT( data->Name + " is dead!" );
}
#include "BaseCharacter.h"
#include "PC_MoBArtFX.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Defines.h"
#include <Kismet/GameplayStatics.h>

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

	//  check team
	if (DamageEvent.IsOfType(FMobaDamageEvent::ClassID))
	{
		FMobaDamageEvent* const moba_damage_event = (FMobaDamageEvent*) &DamageEvent;

		if (Team != EMobaTeam::NONE && Team == moba_damage_event->Team)
		{
			return 0.0f;
		}
	}
	else
	{
		kPRINT_WARNING("A damage has been send without the moba damage event struct.");
	}

	//  mitigate damage
	float took_damage = Super::TakeDamage( Damage, DamageEvent, EventInstigator, DamageCauser );
	took_damage = MitigateDamage( took_damage, DamageCauser );

	//  apply damage
	data->CurrentHealth = FMath::Max( 0.0f, data->CurrentHealth - took_damage );

	//  check death
	if ( data->CurrentHealth == 0.0f )
	{
		HandleDeath();
	}

	return took_damage;
}

float ABaseCharacter::MitigateDamage_Implementation( float damage, AActor* causer )
{
	return damage;
}

void ABaseCharacter::ApplySpellCooldown( float time, EMobaAbilitySlot type )
{
	//  register time
	SpellTimers.Add( type, GetWorld()->GetTimeSeconds() + time );

	//  update hud
	if ( IsValid( CustomPlayerController ) )
	{
		CustomPlayerController->ApplySpellCooldownOnHUD( time, type );
	}

	//  debug
	auto data = GetPlayerDatas();
	if ( IsValid( data ) )
	{
		auto type_name = StaticEnum<EMobaAbilitySlot>()->GetValueAsString( type );
		kLOG_ARGS( "%s: %s is on cooldown for %fs!", *data->Name, *type_name, time );
	}
}

float ABaseCharacter::GetSpellCooldown( EMobaAbilitySlot type ) const
{
	auto itr = SpellTimers.Find( type );
	if ( itr == nullptr ) return 0.0f;

	return *itr - GetWorld()->GetTimeSeconds();
}

void ABaseCharacter::AlterateSpeed(float alteration, float duration)
{
	SpeedAlterations.Add(FSpeedAlteration{ alteration, duration }); 
	ChangeSpeed();
}

bool ABaseCharacter::IsSpellOnCooldown( EMobaAbilitySlot type ) const
{
	return GetSpellCooldown( type ) > 0.0f;
}

void ABaseCharacter::SetTeam(EMobaTeam newTeam)
{
	Team = newTeam;

	//  do other stuff if necessary
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//  get player controller
	CustomPlayerController = GetController<APC_MoBArtFX>();

	//  get player state
	CustomPlayerState = GetPlayerState<APS_MoBArtFX>();
	if ( CustomPlayerState == nullptr && IsValid( CustomPlayerController ) )
	{
		kERROR_LOG_ARGS( "A Player-Controlled Character doesn't have a valid Player State!" );
	}
	
	//  setup data
	SetPlayerDatas( GetPlayerDatas() );
}

void ABaseCharacter::OnRep_PlayerState() 
{
	kPRINT_ERROR("OnRep_PlayerState!");
	CustomPlayerState = GetPlayerState<APS_MoBArtFX>();

	SetPlayerDatas(GetPlayerDatas());

	AHUD_MoBArtFX* hud = Cast<AHUD_MoBArtFX>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud) 
	{
		hud->BeginPlay();
	}
}

void ABaseCharacter::SetPlayerDatas( UPlayerInfos* data )
{
	if (!IsValid(CustomPlayerState)) 
	{
		kPRINT_ERROR("A Character doesn't have a CustomPlayerState!");
		return;
	}

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
		kPRINT_ERROR("PlayerState has not been retrieved!");
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

	int nb_alterations = SpeedAlterations.Num();
	if (nb_alterations > 0)
	{
		float change = 1.0f;
		for (int i = 0; i < nb_alterations; i++)
		{
			SpeedAlterations[i].duration -= DeltaTime; 
			if (SpeedAlterations[i].duration <= 0.0f) 
			{
				SpeedAlterations.RemoveAt(i); 
				i--; 
				nb_alterations--; 
				ChangeSpeed(); 
			}
			else
			{
				change *= SpeedAlterations[i].change;
			}
		}
		kPRINT_TICK("Speed currently altered by a factor of " + FString::SanitizeFloat(change) + ".");
	}
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

void ABaseCharacter::ChangeSpeed()
{
	float change = 1.0f;

	for (auto alteration : SpeedAlterations)
	{
		change *= alteration.change; 
	}

	GetCharacterMovement()->MaxWalkSpeed = GetPlayerDatas()->MaxWalkSpeed * change;
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

void ABaseCharacter::HandleDeath()
{
	auto data = GetPlayerDatas();
	if (!IsValid(data)) return;

	kPRINT(data->Name + " is dead!");

	Death(); //  character's specific death implementation


	//  death logic
	CustomPlayerController->UnPossess();
}
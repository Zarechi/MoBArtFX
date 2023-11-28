// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GregMatt/Needle_Player.h"
#include "Characters/GregMatt/Needle.h"
#include "Characters/GregMatt/Needle_Damage_System.h"
#include <Kismet/GameplayStatics.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ANeedle_Player::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), FoundActors);

	int foundActorCount = FoundActors.Num();
	for (int i = 0; i < foundActorCount; i++)
	{
		if (FoundActors[i] == this)
			continue;

		UNeedle_Damage_System* Component = NewObject<UNeedle_Damage_System>(FoundActors[i]);
		FoundActors[i]->AddInstanceComponent(Component);
		Component->OnComponentCreated();
		Component->RegisterComponent();
		FoundActors[i]->RerunConstructionScripts();
	}

	if (IsAI)
		return;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);

		}
	}
}

void ANeedle_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(SwitchTypeInputAction, ETriggerEvent::Triggered, this, &ANeedle_Player::SwitchAttackType);

	}
}

void ANeedle_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (poisonDamage >= 0)
	{
		poisonDamage -= DeltaTime * 10;
		CurrentHealth -= DeltaTime * 10;
	}
	if (antiHealCurrentCooldown > 0)
		antiHealCurrentCooldown -= DeltaTime;
	if (slowDownCurrentCooldown > 0)
		slowDownCurrentCooldown -= DeltaTime;
	if (stunCurrentCooldown > 0)
		stunCurrentCooldown -= DeltaTime;*/
	if (dodgeCurrentCooldown > 0)
		dodgeCurrentCooldown -= DeltaTime;

	if (BasicAttackCurrentCooldown > 0)
		BasicAttackCurrentCooldown -= DeltaTime;
	if (SkillShotCurrentCooldown > 0)
		SkillShotCurrentCooldown -= DeltaTime;
	//if (DodgeSkillShootCurrentCooldown > 0)
	//	DodgeSkillShootCurrentCooldown -= DeltaTime;
	if (TeleportCurrentCooldown > 0)
		TeleportCurrentCooldown -= DeltaTime;
	if (UltimateCurrentCooldown > 0)
		UltimateCurrentCooldown -= DeltaTime;
}

void ANeedle_Player::Spell_01_Implementation()
{
	if (SkillShotCurrentCooldown <= 0)
	{
		SkillShotCurrentCooldown = SkillShotCooldown;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Spell01 (SkillShot)"));
		ShootProjectile(1);
	}
}

void ANeedle_Player::Spell_02_Implementation()
{
	if (TeleportCurrentCooldown <= 0)
	{
		TeleportCurrentCooldown = TeleportCooldown;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Spell02 (Teleport)"));
		ShootProjectile(2);
	}
}

void ANeedle_Player::Ultimate_Implementation()
{
	if (UltimateCurrentCooldown <= 0)
	{
		UltimateCurrentCooldown = UltimateCooldown;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Ultimate"));

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), FoundActors);

		int foundActorCount = FoundActors.Num();

		int foundNeedleCount = 0;
		for (int i = 0; i < foundActorCount; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1,2.0f, FColor::Yellow, TEXT("foundActorCount"));
			UNeedle_Damage_System* player = (UNeedle_Damage_System*)FoundActors[i]->GetComponentByClass(UNeedle_Damage_System::StaticClass());
			if (FoundActors[i] != GetOwner())
			{
				foundNeedleCount += player->needleStack.Num();
			}
		}

		if (foundNeedleCount >= 2)
		{
			for (int i = 0; i < foundActorCount; i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("A"));
				//UNeedle_Damage_System* player = (UNeedle_Damage_System*)FoundActors[i];
				UNeedle_Damage_System* player = (UNeedle_Damage_System*)FoundActors[i]->GetComponentByClass(UNeedle_Damage_System::StaticClass());
				if (FoundActors[i] != GetOwner())
				{
					player->Hit(CurrentAttackType, NeedleBaseDamage);
				}
			}
		}
	}
}

void ANeedle_Player::AutoAttack_Implementation()
{
	if (BasicAttackCurrentCooldown <= 0)
	{
		BasicAttackCurrentCooldown = BasicAttackCooldown;

		/*AMobaRtFxCharacter* player = (AMobaRtFxCharacter*)GetOwner();

		AMobaHUD* playerHUD;
		playerHUD = Cast<AMobaHUD>(player->GetPlayerState()->GetPlayerController()->GetHUD());
		playerHUD->OnAttackTrigger();*/

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack"));

		ShootProjectile(0);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("AutoAttack"));
	}
}

void ANeedle_Player::Reload_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Reload"));
}

//void ANeedle_Player::Death_Implementation()
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Death"));
//}

void ANeedle_Player::ShootProjectile(int attType)
{
	if (UWorld* World = GetWorld())
	{
		APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AActor* cam = pc->PlayerCameraManager;

		FVector pos = cam->GetActorLocation();
		FRotator rotation = cam->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		AActor* proj = World->SpawnActor(ProjectileClass, &pos, &rotation);
		if (IsValid(proj))
		{
			ANeedle* needle = (ANeedle*)proj;
			needle->Player = this;

			needle->Damage = NeedleBaseDamage;
			needle->Type = CurrentAttackType;
			needle->SlownessDelay = SlownessDelay;
			needle->StunDelay = StunDelay;
			if (attType == 1)
			{
				needle->IsSkillShot = true;
			}
			else if (attType == 2)
			{
				needle->IsTeleport = true;
			}
		}
	}
}

void ANeedle_Player::SwitchAttackType()
{
	//Switch type
	CurrentAttackType = (AttackType)(CurrentAttackType + 1);

	// Go to the beginning if it was the last type
	if (CurrentAttackType == TypeCount)
	{
		CurrentAttackType = (AttackType)0;
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("SwitchAttackType"));
}

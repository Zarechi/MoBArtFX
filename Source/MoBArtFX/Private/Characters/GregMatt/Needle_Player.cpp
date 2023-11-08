// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GregMatt/Needle_Player.h"
#include <Kismet/GameplayStatics.h>

void ANeedle_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (poisonDamage >= 0)
	{
		poisonDamage -= DeltaTime * 10;
		CurrentHealth -= DeltaTime * 10;
	}
	if (antiHealCurrentCooldown > 0)
		antiHealCurrentCooldown -= DeltaTime;
	if (slowDownCurrentCooldown > 0)
		slowDownCurrentCooldown -= DeltaTime;
	if (stunCurrentCooldown > 0)
		stunCurrentCooldown -= DeltaTime;
	if (dodgeCurrentCooldown > 0)
		dodgeCurrentCooldown -= DeltaTime;

	if (BasicAttackCurrentCooldown > 0)
		BasicAttackCurrentCooldown -= DeltaTime;
	if (SkillShotCurrentCooldown > 0)
		SkillShotCurrentCooldown -= DeltaTime;
	if (DodgeSkillShootCurrentCooldown > 0)
		DodgeSkillShootCurrentCooldown -= DeltaTime;
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
		/*UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMobaRtFxCharacter::StaticClass(), FoundActors);
		int foundActorCount = FoundActors.Num();

		int foundNeedleCount = 0;
		for (int i = 0; i < foundActorCount; i++)
		{
			AMobaRtFxCharacter* player = (AMobaRtFxCharacter*)FoundActors[i];
			if (FoundActors[i] != GetOwner())
			{
				foundNeedleCount += player->needleStack.Num();
			}
		}

		if (foundNeedleCount >= 2)
		{
			for (int i = 0; i < foundActorCount; i++)
			{
				AMobaRtFxCharacter* player = (AMobaRtFxCharacter*)FoundActors[i];
				if (FoundActors[i] != GetOwner())
				{
					player->Hit(CurrentAttackType, NeedleBaseDamage);
				}
			}
		}*/
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
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Reload"));
}

void ANeedle_Player::Death_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Death"));
}

void ANeedle_Player::Hit(TEnumAsByte<AttackType> type, float damage)
{
	int maxStack = 5;
	int stackCount = needleStack.Num();
	int stackCountForMultiplier = stackCount % maxStack;

	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("stackCount: ") + FString::FromInt(stackCount));
	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("stackCountForMultiplier: ") + FString::FromInt(stackCountForMultiplier));
	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("damage avant: ") + FString::Printf(TEXT("%f"), damage));
	if (stackCount <= maxStack)
	{
		damage = damage + damage * 0.050f * stackCount;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("damage apres: ") + FString::Printf(TEXT("%f"), damage));
	float damageMultiplied = damage;
	if (stackCount >= maxStack && stackCount != 9)
	{
		damageMultiplied = damageMultiplied * (1.15f + 0.025f * stackCountForMultiplier);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("damage final: ") + FString::Printf(TEXT("%f"), damageMultiplied));
	// Add the attack to stack if the stack is empty or if the current stack is the same type of the attack or if the max stack if reached
	if (stackCount == 0 || needleStack[stackCount - 1] == type || stackCount == maxStack)
	{
		needleStack.Add(type);
		stackCount++;
	}
	else // Or reset stack
	{
		needleStack.Empty();
		stackCount = 0;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("stackCount: ") + FString::FromInt(stackCount));
	if (stackCount == maxStack)
	{
		if (needleStack[0] == AttackType::Fire)
		{
			CurrentHealth -= 150;
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Done: Apply Fire effet"));
		}
		else if (needleStack[0] == AttackType::Poison)
		{
			poisonDamage = 215;
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Done: Apply Poison effet"));
		}
		else if (needleStack[0] == AttackType::AntiHeal)
		{
			antiHealCurrentCooldown = 4;
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Done: Apply AntiHeal effet"));
		}
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Apply stack effet"));
	}
	else if (stackCount == maxStack * 2)
	{
		if (needleStack[0] == AttackType::Fire && needleStack[maxStack] == AttackType::Poison ||
			needleStack[0] == AttackType::Poison && needleStack[maxStack] == AttackType::Fire)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Not done: Crée une explosion Rapide damage flat"));
			//Crée une explosion Rapide damage flat
		}
		else if (needleStack[0] == AttackType::Fire && needleStack[maxStack] == AttackType::AntiHeal ||
			needleStack[0] == AttackType::AntiHeal && needleStack[maxStack] == AttackType::Fire)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Not done: Applique une zone de fournaise qui applique des dégâts par intervalles aux personnages qui entrent dedans."));
			// Applique une zone de fournaise qui applique des dégâts par intervalles aux personnages qui entrent dedans.
		}
		else if (needleStack[0] == AttackType::AntiHeal && needleStack[maxStack] == AttackType::Poison ||
			needleStack[0] == AttackType::Poison && needleStack[maxStack] == AttackType::AntiHeal)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Not done: Crée un nuage, qui gêne fortement la vision avec la forme d’un mur qui applique cet effet sur la durée donc anti heal + poison"));
			// Crée un nuage, qui gêne fortement la vision avec la forme d’un mur qui applique cet effet sur la durée donc anti heal + poison
		}
		else
		{
			needleStack.Empty();
		}
	}

	if (stackCount != 10)
		CurrentHealth -= damageMultiplied;

	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("New player health: ") + FString::FromInt(CurrentHealth));

	if (CurrentHealth <= 0 && IsAI)
	{
		Destroy();
	}

	//if (!IsAI)
	//{
	//	AMobaHUD* playerHUD;
	//	playerHUD = Cast<AMobaHUD>(GetPlayerState()->GetPlayerController()->GetHUD());
	//	playerHUD->OnGetHit();
	//	playerHUD->UpdateWidgetHealth(CurrentHealth);
	//}
	//else
	//	UpdateAIHealth(CurrentHealth);
}

void ANeedle_Player::SkillShotHit()
{
	slowDownCurrentCooldown = SlownessDelay;
	int stackCount = needleStack.Num();
	if (stackCount == 5)
	{
		stunCurrentCooldown = StunDelay;
	}
}

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
			//ANeddle* needle = (ANeddle*)proj;
			//needle->Damage = NeedleBaseDamage;
			//needle->Type = CurrentAttackType;
			////needle->Player = pc;
			//needle->Player = GetOwner();
			//if (attType == 1)
			//{
			//	needle->IsSkillShot = true;
			//}
			//else if (attType == 2)
			//{
			//	needle->IsTeleport = true;
			//}
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
}

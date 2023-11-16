


#include "Characters/GregMatt/Needle_Damage_System.h"
#include "Engine/EngineTypes.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UNeedle_Damage_System::UNeedle_Damage_System()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UNeedle_Damage_System::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, this->GetOwner()->GetActorLabel());
	charMov = this->GetOwner()->GetComponentByClass<UCharacterMovementComponent>();
	if (charMov)
	{
		normalMoveSpeed = charMov->MaxWalkSpeed;
		//charMov->MaxWalkSpeed /= 10.0f;
	}
}


// Called every frame
void UNeedle_Damage_System::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (poisonDamage > 0)
	{
		float damageSpeed = 10;
		poisonDamage -= DeltaTime * damageSpeed;
		if (ABaseCharacter* player = CastChecked<ABaseCharacter>(this->GetOwner()))
		{
			ApplyDmg(DeltaTime * damageSpeed);
		}
	}
	if (antiHealCurrentCooldown > 0)
		antiHealCurrentCooldown -= DeltaTime;

	if (slowDownCurrentCooldown > 0)
	{
		slowDownCurrentCooldown -= DeltaTime;
		if (charMov)
		{
			charMov->MaxWalkSpeed = normalMoveSpeed / 2.0f;
		}
	}
	else 
	{
		if (charMov)
		{
			charMov->MaxWalkSpeed = normalMoveSpeed;
		}
	}

	if (stunCurrentCooldown > 0)
	{
		stunCurrentCooldown -= DeltaTime;
		if (charMov)
		{
			charMov->MaxWalkSpeed = 0;
		}
	}
}

void UNeedle_Damage_System::Hit(TEnumAsByte<AttackType> type, float damage)
{
	if (ABaseCharacter* player = CastChecked<ABaseCharacter>(this->GetOwner()))
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
				ApplyDmg(150);
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
			ApplyDmg(damageMultiplied);

		//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow, TEXT("New player health: ") + FString::FromInt(CurrentHealth));

		//if (CurrentHealth <= 0 && IsAI)
		//{
		//	Destroy();
		//}

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
}

void UNeedle_Damage_System::SkillShotHit(float SlownessDelay, float StunDelay)
{
	slowDownCurrentCooldown = SlownessDelay;
	int stackCount = needleStack.Num();
	if (stackCount == 5)
	{
		stunCurrentCooldown = StunDelay;
	}
}

void UNeedle_Damage_System::ApplyDmg(float damage)
{
	if (ABaseCharacter* player = CastChecked<ABaseCharacter>(this->GetOwner()))
	{
		UGameplayStatics::ApplyDamage(player, damage, GetWorld()->GetFirstPlayerController(), GetOwner(), UDamageType::StaticClass());
	}
}


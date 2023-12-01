#include "Characters/Cainer/CainerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PC_MoBArtFX.h"



ACainerCharacter::ACainerCharacter()
{
}

void ACainerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//  retrieves infos
	infos = Cast<UCainerInfos>(GetPlayerDatas());
	if(infos.IsNull()) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, "WARNING : Cainer doesn't have the correct player infos !");

	//  set ultimate cooldown at max
	//ApplySpellCooldown(infos->Ultimate_CD, EMobaAbilitySlot::Ultimate);
}

void ACainerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACainerCharacter::AutoAttack_Implementation()
{
	if (infos->CurrentAmmo <= 0)
	{
		Reload();
	}
	else
	{
		infos->CurrentAmmo--;
	}
}

void ACainerCharacter::Reload_Implementation()
{
	infos->CurrentAmmo = infos->MaxAmmo;
}


void ACainerCharacter::Spell_01_Implementation() //  speed boost
{
	//  TODO implement gameplay state system to check if character can cast the spell


	if (GetSpellCooldown(EMobaAbilitySlot::First) > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Spell_01 : Speed Boost on cooldown for " + FString::SanitizeFloat(GetSpellCooldown(EMobaAbilitySlot::First)) + " seconds.");
		return;
	}


	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Spell_01 : Speed Boost");
	ApplySpellCooldown(infos->Spell01_CD, EMobaAbilitySlot::First);

	TArray<FHitResult> outs;


	bool hit = GetWorld()->SweepMultiByObjectType(outs, GetActorLocation(), GetActorLocation(), FQuat(), FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(infos->speedBoostRadius));

	if (!hit)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, "Speed boost ability found no actor (bruh).");
		return;
	}

	TArray<ABaseCharacter*> checked_chara; 

	for (FHitResult out : outs)
	{
		auto chara = Cast<ABaseCharacter>(out.GetActor());
		if (!chara->IsValidLowLevel()) continue;

		if (checked_chara.Contains(chara)) continue;
		checked_chara.Add(chara);

		chara->AlterateSpeed(infos->speedBoostValue, infos->speedBoostDuration);
	}

	if (IsValid(monstro))
	{
		if (FVector::Distance(GetActorLocation(), monstro->GetActorLocation()) < infos->speedBoostRadius)
		{
			monstro->BoostSpeed(infos->speedBoostValue, infos->speedBoostDuration);
		}
	}
}

void ACainerCharacter::Spell_02_Implementation() //  monstro
{
	//  TODO implement gameplay state system to check if character can cast the spell


	if (GetSpellCooldown(EMobaAbilitySlot::Second) > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Spell_02 : Monstro on cooldown for " + FString::SanitizeFloat(GetSpellCooldown(EMobaAbilitySlot::Second)) + " seconds.");
		return;
	}


	if (IsValid(monstro)) //  monstro already exists 
	{
		monstro->Destroy(); 
	}

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Spell_02 : Monstro");
	ApplySpellCooldown(infos->Spell02_CD, EMobaAbilitySlot::Second);


	FTransform monstro_transform; 
	monstro_transform.SetLocation(GetActorLocation()); 
	monstro_transform.SetRotation(GetActorRotation().Quaternion()); 

	monstro = GetWorld()->SpawnActor<ACainerMonstro>(infos->monstroBlueprint, monstro_transform); 
	monstro->SetBaseSpeed(infos->monstroMoveSpeed); 
	monstro->SetLife(infos->monstroLife); 
}

void ACainerCharacter::PingMonstro()
{
	if (!IsValid(monstro))
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Ping Monstro");

	FVector monstro_dest = GetMonstroDestination();

	if (monstro_dest == FVector::ZeroVector) return;

	monstro_dest += FVector::UpVector * 15.0f;

	monstro->SetDestination(monstro_dest, GetActorRotation().Yaw);
}

void ACainerCharacter::Ultimate_Implementation() //  flash
{
	//  TODO implement gameplay state system to check if character can cast the spell


	if (GetSpellCooldown(EMobaAbilitySlot::Ultimate) > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Ultimate : Flash on cooldown for " + FString::SanitizeFloat(GetSpellCooldown(EMobaAbilitySlot::Ultimate)) + " seconds.");
		return;
	}


	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Ultimate : Flash");
	ApplySpellCooldown(infos->Ultimate_CD, EMobaAbilitySlot::Ultimate);


	TArray<FHitResult> outs; 

	bool hit = GetWorld()->SweepMultiByObjectType(outs, GetActorLocation(), GetActorLocation(), FQuat(), FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(infos->flashRange));

	if (!hit)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, "Ultimate flash ability from Cainer found no actor (bruh).");
		return;
	}

	TArray<ACharacter*> checked_chara;

	for (FHitResult out : outs)
	{
		auto chara = Cast<ACharacter>(out.GetActor());
		if (!chara->IsValidLowLevel()) continue;

		if (chara == this) continue;

		if (checked_chara.Contains(chara)) continue;
		checked_chara.Add(chara);


		auto speed_comp = chara->GetComponentByClass<UAC_CainerFlash>();
		if (!speed_comp->IsValidLowLevel()) continue;

		FVector flash_direction = chara->GetActorLocation() - GetActorLocation();
		flash_direction.Normalize();
		if (FVector::DotProduct(GetActorForwardVector(), flash_direction) > 0.6f && FVector::DotProduct(chara->GetActorForwardVector(), -flash_direction) > 0.6f)
		{
			speed_comp->Flash(infos->flashDuration);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Flashed " + chara->GetName() + ". (by Cainer)");
		}
	}

	if (!IsValid(monstro)) return;

	outs.Empty();

	hit = GetWorld()->SweepMultiByObjectType(outs, monstro->GetActorLocation(), monstro->GetActorLocation(), FQuat(), FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(infos->flashRange));

	if (!hit)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, "Ultimate flash ability from Cainer's monstro found no actor (bruh).");
		return;
	}

	for (FHitResult out : outs)
	{
		auto chara = Cast<ACharacter>(out.GetActor());
		if (!chara->IsValidLowLevel()) continue;

		if (checked_chara.Contains(chara)) continue;
		checked_chara.Add(chara);


		auto speed_comp = chara->GetComponentByClass<UAC_CainerFlash>();
		if (!speed_comp->IsValidLowLevel()) continue;

		FVector flash_direction = chara->GetActorLocation() - monstro->GetActorLocation();
		flash_direction.Normalize();
		if (FVector::DotProduct(monstro->GetActorForwardVector(), flash_direction) > 0.7f && FVector::DotProduct(chara->GetActorForwardVector(), -flash_direction) > 0.7f)
		{
			speed_comp->Flash(infos->flashDuration);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Flashed " + chara->GetName() + ". (by Cainer's monstro)");
		}
	}
}

FVector ACainerCharacter::GetMonstroDestination()
{
	FHitResult out;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	FCollisionResponseParams response_params;

	bool hit = Cast<APC_MoBArtFX>(GetController())->CameraTraceSingleByChannel(out, infos->monstroPingMaxDist, ECC_Camera, params, response_params);

	if (!hit) return FVector::ZeroVector;

	if (FVector::DotProduct(out.ImpactNormal, FVector::UpVector) < 0.8f) return FVector::ZeroVector;

	FVector destination = out.ImpactPoint;

	FTransform particles_transform;
	particles_transform.SetTranslation(destination + FVector::UpVector * 70.0f);
	particles_transform.SetRotation(UKismetMathLibrary::RandomRotator().Quaternion());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), infos->monstroPingParticles, particles_transform);


	return destination;
}


void ACainerCharacter::Death_Implementation() {}
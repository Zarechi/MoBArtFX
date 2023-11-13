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
	flashCrtCD = infos->Ultimate_CD;
}

void ACainerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//  decrease cooldowns each frame
	monstroCrtCD = fmax(monstroCrtCD - DeltaTime, 0.0f);
	speedBoostCrtCD = fmax(speedBoostCrtCD - DeltaTime, 0.0f);
	flashCrtCD = fmax(flashCrtCD - DeltaTime, 0.0f);
}


void ACainerCharacter::AutoAttack_Implementation()
{
	if (GetPlayerDatas()->CurrentAmmo <= 0)
	{
		GetPlayerDatas()->CurrentAmmo = 0;
		Reload();
	}
}

void ACainerCharacter::Reload_Implementation()
{
	GetPlayerDatas()->CurrentAmmo = GetPlayerDatas()->MaxAmmo;
}


void ACainerCharacter::Spell_01_Implementation() //  speed boost
{
	//  TODO implement gameplay state system to check if character can cast the spell


	if (speedBoostCrtCD > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Spell_01 : Speed Boost on cooldown for " + FString::SanitizeFloat(speedBoostCrtCD) + " seconds.");
		return;
	}


	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Spell_01 : Speed Boost");
	speedBoostCrtCD = infos->Spell01_CD;


}

void ACainerCharacter::Spell_02_Implementation() //  monstro
{
	//  TODO implement gameplay state system to check if character can cast the spell


	if (monstroCrtCD > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Spell_02 : Monstro on cooldown for " + FString::SanitizeFloat(monstroCrtCD) + " seconds.");
		return;
	}


	if (IsValid(monstro)) //  monstro already exists 
	{
		monstro->Destroy(); 
	}

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Spell_02 : Monstro");
	monstroCrtCD = infos->Spell02_CD;


	FTransform monstro_transform; 
	monstro_transform.SetLocation(GetActorLocation()); 
	monstro_transform.SetRotation(GetActorRotation().Quaternion()); 

	monstro = GetWorld()->SpawnActor<ACainerMonstro>(infos->monstroBlueprint, monstro_transform); 
	monstro->SetSpeed(infos->monstroMoveSpeed); 
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


	if (flashCrtCD > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Cyan, "Ultimate : Flash on cooldown for " + FString::SanitizeFloat(flashCrtCD) + " seconds.");
		return;
	}


	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Blue, "Ultimate : Flash");
	flashCrtCD = infos->Ultimate_CD;


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
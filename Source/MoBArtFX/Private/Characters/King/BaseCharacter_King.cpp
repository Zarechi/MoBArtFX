// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/BaseCharacter_King.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include <Characters/King/Projectile.h>
#include "MobaGameplayStatics.h"
#include <Defines.h>

ABaseCharacter_King::ABaseCharacter_King()
{
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	SpellSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpellSpawnPoint"));
	SpellSpawnPoint->SetupAttachment(GetCapsuleComponent());
	SpellSpawnPoint->SetRelativeLocation(FVector(150.f, 0.f, 0.f));

	// Create as mesh for God Hand Ability
	MeshGodHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshGodHand"));
	MeshGodHand->SetupAttachment(SpellSpawnPoint);
	MeshGodHand->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	MeshGodHand->SetRelativeScale3D(FVector(0.2f, 0.95f, 1.3f));
	MeshGodHand->SetVisibility(false);
	MeshGodHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshGodHand->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshGodHand->BodyInstance.SetCollisionProfileName("Shield");
	//MeshGodHand->OnComponentHit.AddDynamic(this, &AC_Moba::OnHit);

	// Create as mesh for Ultimate L Hand
	UltimateLHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshUltimateLHand"));
	UltimateLHand->SetupAttachment(SpellSpawnPoint);
	UltimateLHand->SetRelativeLocation(FVector(-10.f, -100.f, 0.f));
	UltimateLHand->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	UltimateLHand->SetVisibility(false);
	UltimateLHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UltimateLHand->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//UltimateLHand->OnComponentBeginOverlap.AddDynamic(this, &AC_Moba::OnOverlapBegin);

	// Create as mesh for Ultimate R Hand
	UltimateRHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshUltimateRHand"));
	UltimateRHand->SetupAttachment(SpellSpawnPoint);
	UltimateRHand->SetRelativeLocation(FVector(-10.f, 100.f, 0.f));
	UltimateRHand->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	UltimateRHand->SetVisibility(false);
	UltimateRHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UltimateRHand->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//UltimateRHand->OnComponentBeginOverlap.AddDynamic(this, &AC_Moba::OnOverlapBegin);

	SetActorTickInterval(0.1);
}

void ABaseCharacter_King::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	GetCharacterMovement()->GravityScale = DefaultGravityScale;

	currentGodHandHealth = AbilityHealth;

	data = GetPlayerDatas();
}

void ABaseCharacter_King::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timerDefaultAttack -= DeltaTime;
	timerGodHandBreack -= DeltaTime;
	timerIronShears -= DeltaTime;
	timerUlti -= DeltaTime;
	timerUltiActive -= DeltaTime;

	if (timerIronShears <= 0)
	{
		Spell02IsActive = false;
	}

	if (UltiIsActive && timerUltiActive <= 0)
	{
		EndUltimate();
	}

	if (Spell01IsActive && data->CurrentHealth <= saveCurentHealth)
	{
		EndGodHand();
	}
}

void ABaseCharacter_King::AutoAttack_Implementation()
{
	if (!UltiIsActive && !Spell01IsActive && timerDefaultAttack <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, SpellSpawnPoint->GetComponentLocation().ToString());
		timerDefaultAttack = AttackRate;
		ApplySpellCooldown(timerDefaultAttack, EMobaAbilitySlot::AutoAttack);
		TObjectPtr<AActor> proj;
		proj = GetWorld()->SpawnActor<AActor>(ProjectilClass, SpellSpawnPoint->GetComponentLocation(), FirstPersonCameraComponent->GetComponentRotation() + Calibrate);
		TObjectPtr<AProjectile> projectil = Cast<AProjectile>(proj);
		projectil->SetShooter(this);
	}
}

void ABaseCharacter_King::Spell_01_Implementation()
{
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
		{
			//Spell01IsActive = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("God Hand"));
			GetCharacterMovement()->MaxWalkSpeed = AbilityMaxWalkSpeed;
			MeshGodHand->SetVisibility(true);
			MeshGodHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			saveCurentHealth = data->CurrentHealth;
			if (data->CurrentHealth > 0)
			{
				data->CurrentHealth += AbilityHealth;

			}
		}
	);

	if (!UltiIsActive && timerGodHandBreack < 0 && !Spell01IsActive)
	{
		Spell01IsActive = true;
		FTimerHandle TimerH;
		GetWorld()->GetTimerManager().SetTimer(TimerH, Delegate, abilityActivationTime, false);
		if (godHandBreak)
		{
			currentGodHandHealth = AbilityHealth;
			godHandBreak = false;
		}
	}
}

void ABaseCharacter_King::Spell_02_Implementation()
{
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
		{
			if (!Spell02IsActive)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ability2"));
				GetWorld()->SpawnActor<AActor>(ActorAbility2, SpellSpawnPoint->GetComponentLocation(), GetCapsuleComponent()->GetComponentRotation());
				timerIronShears = cooldownAbility2;
				ApplySpellCooldown(timerIronShears, EMobaAbilitySlot::Second);
				Spell02IsActive = true;
			}
		}
	);

	if (!UltiIsActive && timerIronShears <= 0)
	{
		FTimerHandle TimerH;
		GetWorld()->GetTimerManager().SetTimer(TimerH, Delegate, ability2ActivationTime, false);
	}
}

void ABaseCharacter_King::Ultimate_Implementation()
{
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
		{
			if (!UltiIsActive)
			{
				UltiIsActive = true;
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ultimate"));

				saveGravityScale = GetCharacterMovement()->GravityScale;
				GetCharacterMovement()->GravityScale = 0.f;

				saveBrakingFrictionFactor = GetCharacterMovement()->BrakingFrictionFactor;
				GetCharacterMovement()->BrakingFrictionFactor = 0.f;

				GetCapsuleComponent()->AddLocalOffset(FVector(0.f, 0.f, LevitationHeight));

				UltimateLHand->SetVisibility(true);
				UltimateLHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				UltimateRHand->SetVisibility(true);
				UltimateRHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				timerUltiActive = UltiDuration;
			}
		}
	);

	if (timerUlti <= 0)
	{
		FTimerHandle TimerH;
		GetWorld()->GetTimerManager().SetTimer(TimerH, Delegate, UltiActivationTime, false);
	}
}

void ABaseCharacter_King::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AProjectile* proj = Cast<AProjectile>(OtherActor);
	if (proj != nullptr)
	{
		currentGodHandHealth -= proj->GetDamage();
		OtherActor->Destroy();

		//FString currentFHHealthStr = FString::SanitizeFloat(currentGodHandHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::SanitizeFloat(currentGodHandHealth));

		//if (currentGodHandHealth <= proj->GetDamage())
		if (currentGodHandHealth <= proj->GetDamage())
		{
			EndGodHand();
			godHandBreak = true;
			timerGodHandBreack = cooldownAbilityBreak;
			ApplySpellCooldown(timerGodHandBreack, EMobaAbilitySlot::First);
		}
	}
}

void ABaseCharacter_King::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ABaseCharacter> target = Cast<ABaseCharacter>(OtherActor);

	if (target != nullptr)
	{
		UMobaGameplayStatics::ApplyMobaDamage(target, UltiDemage, this, this);
	}

}

void ABaseCharacter_King::Spell_01End_Implementation()
{
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("EndAbility1"));
			EndGodHand();
		}
	);

	Spell01IsActive = false;
	FTimerHandle TimerH;
	GetWorld()->GetTimerManager().SetTimer(TimerH, Delegate, abilityActivationTime, false);
}

void ABaseCharacter_King::EndGodHand()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	MeshGodHand->SetVisibility(false);
	MeshGodHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Spell01IsActive = false;

	data->CurrentHealth = saveCurentHealth;
}

void ABaseCharacter_King::EndUltimate()
{
	UltiIsActive = false;
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("EndUltimate"));

			UltimateLHand->SetVisibility(false);
			UltimateLHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			UltimateRHand->SetVisibility(false);
			UltimateRHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			GetCharacterMovement()->GravityScale = saveGravityScale;
			GetCharacterMovement()->BrakingFrictionFactor = saveBrakingFrictionFactor;

			GetCapsuleComponent()->AddLocalOffset(FVector(0.f, 0.f, -LevitationHeight));

			timerUlti = UltiCooldown;
			ApplySpellCooldown(timerUlti, EMobaAbilitySlot::Ultimate);
		}
	);

	FTimerHandle TimerH;
	GetWorld()->GetTimerManager().SetTimer(TimerH, Delegate, UltiRetractationTime, false);
}

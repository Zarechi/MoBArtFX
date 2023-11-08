// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/King/BaseCharacter_King.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

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

void ABaseCharacter_King::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timerDefaultAttack -= DeltaSeconds;
}

void ABaseCharacter_King::AutoAttack_Implementation()
{
	if (!UltiIsActive && !Spell01IsActive && timerDefaultAttack <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, SpellSpawnPoint->GetComponentLocation().ToString());
		timerDefaultAttack = AttackRate;
		GetWorld()->SpawnActor<AActor>(ProjectilClass, SpellSpawnPoint->GetComponentLocation(), FirstPersonCameraComponent->GetComponentRotation() + Calibrate);
	}
}

void ABaseCharacter_King::Spell_01_Implementation()
{
}

void ABaseCharacter_King::Spell_02_Implementation()
{
}

void ABaseCharacter_King::Ultimate_Implementation()
{
}

void ABaseCharacter_King::Spell_01End_Implementation()
{
}

void ABaseCharacter_King::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	GetCharacterMovement()->GravityScale = DefaultGravityScale;
}

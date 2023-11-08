#include "Characters/Crow/CharacterCrow.h"
#include "Engine/DamageEvents.h"
#include "MOBA_Projectile.h"

ACharacterCrow::ACharacterCrow()
{
    PrimaryActorTick.bCanEverTick = true;

    // Params for Ability
    CastingTime = 1.0f;
    CooldownTime = 0.4f;
    Damage = 6.0f;

    // Params for Projectile
    ProjectileClass = AMOBA_Projectile::StaticClass();

    LastUsedTime = -CooldownTime;;
    RemainingCooldown = 0.0f;
}

void ACharacterCrow::BeginPlay()
{
    Super::BeginPlay();
}

void ACharacterCrow::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACharacterCrow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterCrow::AutoAttack_Implementation()
{
    // Verify if the capacity is available
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastUsedTime >= CooldownTime)
    {
        // Capacity not in cooldown
        LastUsedTime = CurrentTime;

        // Create projectile (sphère)
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator SpawnRotation = GetActorRotation();
        AMOBA_Projectile* NewProjectile = GetWorld()->SpawnActor<AMOBA_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

        if (NewProjectile)
        {
            // Configurez la direction du projectile (par exemple, en avant)
            FVector ShootDirection = GetActorForwardVector();
            NewProjectile->SetDirection(ShootDirection);
        }
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Auto Attack"));
        
    }
    else
    {
        // Capacity in cooldown
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cooldown in progress"));
    }
}

void ACharacterCrow::Spell_01_Implementation()
{

}

void ACharacterCrow::Spell_02_Implementation()
{

}

void ACharacterCrow::Ultimate_Implementation()
{

}

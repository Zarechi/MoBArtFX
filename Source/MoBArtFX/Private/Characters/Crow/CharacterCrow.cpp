#include "CharacterCrow.h"
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

        if (Owner)
        {
            // Create projectile (sphère)
            FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.0f;
            FRotator SpawnRotation = Owner->GetActorRotation();
            AMOBA_Projectile* NewProjectile = GetWorld()->SpawnActor<AMOBA_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

            if (NewProjectile)
            {
                // Configurez la direction du projectile (par exemple, en avant)
                FVector ShootDirection = Owner->GetActorForwardVector();
                NewProjectile->SetDirection(ShootDirection);
            }
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Auto Attack"));

            //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("SpawnLocation: %s"), *SpawnLocation.ToString()));
            //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("SpawnRotation: %s"), *SpawnRotation.ToString()));
        }
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

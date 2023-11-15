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
    ProjectileSpeed = 3000.0f;

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
    // Verify if the ability is available
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastUsedTime >= CooldownTime)
    {
        // Ability not in cooldown
        LastUsedTime = CurrentTime;
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

        if (PlayerController)
        {
            // Get the camera forward vector
            FVector CameraForwardVector = PlayerController->GetControlRotation().Vector();

            for (int32 i = 0; i < 3; i++)
            {
                // Set the spawn location based on the camera forward vector
                FVector SpawnLocation = GetActorLocation() + CameraForwardVector * (100.0f + i * 100.0f);

                // Create projectile (sphere)
                FRotator SpawnRotation = GetActorRotation();

                // Set the projectile's initial velocity based on the character's forward vector
                FVector ProjectileVelocity = GetActorForwardVector() * ProjectileSpeed;

                AMOBA_Projectile* NewProjectile = GetWorld()->SpawnActor<AMOBA_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

                if (NewProjectile)
                {
                    // Set the projectile's velocity
                    NewProjectile->SetDirection(ProjectileVelocity);
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Auto Attack"));
                }
            }
        }
        
    }
    else
    {
        // Ability in cooldown
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

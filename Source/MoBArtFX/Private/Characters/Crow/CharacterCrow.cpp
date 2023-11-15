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

    // Default Params for Projectile
    ProjectileClass = AMOBA_Projectile::StaticClass();
    ProjectileSpeed = 3000.0f;
    ProjectileLifetime = 1.0f;

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
            // Get the camera forward vector from the player controller
            FVector CameraForwardVector = PlayerController->GetControlRotation().Vector();

            // Define the target location (center of the screen)
            FVector TargetLocation = GetActorLocation() + CameraForwardVector * 1000.0f;

            // Determine the side (right or left)
            float SideMultiplier = (SideCounter % 2 == 0) ? 1.0f : -1.0f;

            for (int32 i = 0; i < 3; i++)
            {
                // Set the spawn location based on the camera forward vector with an offset
                FVector SpawnLocation = GetActorLocation() + CameraForwardVector * (100.0f + i * 100.0f) + FVector(0.0f, SideMultiplier * 50.0f, 0.0f);

                // Calculate the direction towards the target location for each projectile
                FVector ProjectileDirection = (TargetLocation - SpawnLocation).GetSafeNormal();

                // Create projectile (sphere)
                FRotator SpawnRotation = ProjectileDirection.Rotation();

                // Set the projectile's initial velocity based on the character's forward vector
                FVector ProjectileVelocity = CameraForwardVector * ProjectileSpeed;

                AMOBA_Projectile* NewProjectile = GetWorld()->SpawnActor<AMOBA_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

                if (NewProjectile)
                {
                    NewProjectile->SetDirection(ProjectileVelocity);
                    NewProjectile->SetProjectileSpeed(ProjectileSpeed);
                    NewProjectile->SetProjectileLifetime(ProjectileLifetime);

                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Auto Attack"));
                }
            }

            // Increment the side counter for the next set of projectiles
            SideCounter++;
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

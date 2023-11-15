#include "Characters/Crow/CharacterCrow.h"
#include "Engine/DamageEvents.h"
#include "MOBA_Projectile.h"
#include <Kismet/GameplayStatics.h>
#include "DrawDebugHelpers.h"

ACharacterCrow::ACharacterCrow()
{
    PrimaryActorTick.bCanEverTick = true;

    // Params for Ability
    CastingTime = 1.0f;
    AADamage = 6.0f;

    // Default Params for Auto Attack Projectile
    ProjectileClass = AMOBA_Projectile::StaticClass();
    AACD = 0.4f;
    ProjectileSpeed = 3000.0f;
    ProjectileLifetime = 1.0f;

    // Default Params for Redemption Feather
    RedemptionFeatherCD = 1.5f;
    RedemptionFeatherDamage = 40.0f;
    RedemptionFeatherRange = 100.0f;
    RedemptionFeatherKB = 100.0f;

    LastUsedAATime = -AACD;
    LastUsedSpell01Time = -RedemptionFeatherCD;
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
    if (CurrentTime - LastUsedAATime >= AACD)
    {
        // Ability not in cooldown
        LastUsedAATime = CurrentTime;
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
    // Verify if the ability is available
    const float CurrentTime = GetWorld()->GetTimeSeconds();

    if (CurrentTime - LastUsedSpell01Time >= RedemptionFeatherCD)
    {
        LastUsedSpell01Time = CurrentTime;

        FRotator CameraRotation = GetControlRotation();
        FVector ForwardVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::X);

        // Starting point of the raycast
        FVector StartLocation = GetActorLocation() + ForwardVector * 100.0f;

        float RaycastHeight = 50.0f;
        // Final point of the raycast
        FVector EndLocation = StartLocation + ForwardVector * RedemptionFeatherRange + FVector(0.0f, 0.0f, RaycastHeight);

        // Params
        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this); // Ignore player actor

        // Raycast
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, bHit ? FColor::Green : FColor::Red, false, 0.1f, 0, 1.0f);

        // If raycast hit something
        if (bHit)
        {
            // Knockback direction
            FVector RecoilDirection = -ForwardVector;

            // Calculate new position of the player
            FVector NewLocation = GetActorLocation() + RecoilDirection * RedemptionFeatherKB;

            // Define new position of the player
            SetActorLocation(NewLocation);

            // Get hit actor
            AActor* HitActor = HitResult.GetActor();

            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Redemption Feather"));
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Hit: %s, Recoil Applied"), *HitActor->GetName()));
        }
    }
    else
    {
        // Ability in cooldown
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Cooldown in progress"));
    }
}



void ACharacterCrow::Spell_02_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Scarecrow Storm"));
}

void ACharacterCrow::Ultimate_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Vengeful Raven"));
}

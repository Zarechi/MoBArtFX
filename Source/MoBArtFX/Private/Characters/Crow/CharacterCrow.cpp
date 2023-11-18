#include "Characters/Crow/CharacterCrow.h"
#include "Engine/DamageEvents.h"
#include "Characters/Crow/Crow_Projectile.h"
#include <Kismet/GameplayStatics.h>
#include "DrawDebugHelpers.h"

ACharacterCrow::ACharacterCrow()
{
    PrimaryActorTick.bCanEverTick = true;

    // Params for Ability
    CastingTime = 1.0f;
    AADamage = 6.0f;

    // Default Params for Auto Attack Projectile
    ProjectileClass = ACrow_Projectile::StaticClass();
    AACD = 0.4f;
    ProjectileSpeed = 3000.0f;
    ProjectileLifetime = 1.0f;

    // Default Params for Redemption Feather
    RedemptionFeatherCD = 1.5f;
    RedemptionFeatherDamage = 40.0f;
    RedemptionFeatherRange = 150.0f;
    RedemptionFeatherKB = 350.0f;
    DistanceFromChara = 200.0f;

    // Default Params for Scarecrow Breeze
    ScarecrowBreezeCD = 15.0f;
    GlideDuration = 10.0f;
    JumpZVelocity = 2000.0f;
    GlideAirControl = 1.0f;
    DefaultAirControl = 0.3f;
    DefaultGravity = 1.0f;

    // Default Params for CD
    LastUsedAATime = -AACD;
    LastUsedSpell01Time = -RedemptionFeatherCD;
    LastUsedSpell02Time = -ScarecrowBreezeCD;
    LastUsedUltimateTime = -UltimateCD;

    // Initialize the spline component
    CurvedMovementSpline = CreateDefaultSubobject<USplineComponent>(TEXT("CurvedMovementSpline"));
    CurvedMovementSpline->SetupAttachment(RootComponent);
    CurvedMovementSpline->SetHiddenInGame(false); // Hide the spline in the game
}

void ACharacterCrow::BeginPlay()
{
    Super::BeginPlay();
}

void ACharacterCrow::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateGlide();
}

void ACharacterCrow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterCrow::SetupCurvedMovement(FVector TargetLocation)
{
    // Clear existing points from the spline
    CurvedMovementSpline->ClearSplinePoints();

    // Add start and end points to the spline
    CurvedMovementSpline->AddSplinePoint(GetActorLocation(), ESplineCoordinateSpace::World);
    CurvedMovementSpline->AddSplinePoint(GetActorLocation() + FVector(0.0f, 1000.0f, 0.0f), ESplineCoordinateSpace::World);

    // Add a control point to create a curved path
    FVector ControlPoint = FVector(0.0f, 500.0f, 0.0f) + GetActorLocation();
    CurvedMovementSpline->AddSplinePoint(ControlPoint, ESplineCoordinateSpace::World);

    // Set the end point to the target location
    CurvedMovementSpline->AddSplinePoint(TargetLocation, ESplineCoordinateSpace::World);
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

                ACrow_Projectile* NewProjectile = GetWorld()->SpawnActor<ACrow_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

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

        // Starting point of the sphere trace
        FVector StartLocation = GetActorLocation() + ForwardVector * DistanceFromChara;

        // Sphere radius
        float SphereRadius = RedemptionFeatherRange;

        // Params
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this); // Ignore player actor

        TArray<FHitResult> HitResults;

        // Sphere trace
        bool bHit = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, StartLocation, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(SphereRadius), CollisionParams);

        // Draw debug sphere
        DrawDebugSphere(GetWorld(), StartLocation, SphereRadius, 32, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);

        // If sphere trace hits something and the recoil has not been applied yet
        if (bHit && !bRecoilApplied)
        {
            for (const FHitResult& HitResult : HitResults)
            {
                // Verify if an actor is hit
                if (HitResult.GetActor()->IsA(APawn::StaticClass()))
                {
                    // Knockback direction
                    FVector RecoilDirection = -ForwardVector;

                    // Calculate new position of the player
                    FVector NewLocation = GetActorLocation() + RecoilDirection * RedemptionFeatherKB;

                    // Define new position of the player
                    SetActorLocation(NewLocation);

                    // Mark recoil as applied
                    bRecoilApplied = true;

                    // Get hit actor
                    AActor* HitActor = HitResult.GetActor();
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Redemption Feather"));
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Hit: %s, Recoil Applied"), *HitActor->GetName()));
                    break;
                }
            }
        }
    }
    else
    {
        // Ability in cooldown
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Cooldown in progress"));
    }
    // Reset the recoil flag at the end of the function
    bRecoilApplied = false;
}

void ACharacterCrow::Spell_02_Implementation()
{
    // Verify if the ability is available
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("CurrentTime: %f, LastUsedSpell02Time: %f, ScarecrowBreezeCD: %f"), CurrentTime, LastUsedSpell02Time, ScarecrowBreezeCD);

    if (CurrentTime - LastUsedSpell02Time >= ScarecrowBreezeCD)
    {
        LastUsedSpell02Time = CurrentTime;

        // Start Jump
        LaunchCharacter(FVector(0.0f, 0.0f, JumpZVelocity), false, false);

        // Activate Gliding
        bIsGliding = true;
        GlideStartTime = GetWorld()->GetTimeSeconds();

        // Params glide controls
        GetCharacterMovement()->AirControl = GlideAirControl;
    }
    else
    {
        // Ability in cooldown
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Glide ability is on cooldown"));
    }
}

void ACharacterCrow::UpdateGlide()
{
    if (bIsGliding)
    {
        float ElapsedTime = GetWorld()->GetTimeSeconds() - GlideStartTime;

        if (bInfiniteGlideDuration || (ElapsedTime < GlideDuration))
        {
            // Apply new control in air
            FVector HorizontalMovement = FVector(GetPendingMovementInputVector().X, GetPendingMovementInputVector().Y, 0.0f);
            GetCharacterMovement()->AddInputVector(HorizontalMovement * GlideAirControl);

            // Check if the character has reached the highest point of the jump
            if (GetVelocity().Z < 0.0f)
            {
                // Disable gravity for a smoother horizontal glide
                GetCharacterMovement()->GravityScale = 0.0f;
            }
            else
            {
                // Enable gravity when the character starts descending
                GetCharacterMovement()->GravityScale = DefaultGravity;
            }
        }
        else
        {
            // Deactivate gliding at the end of its time
            bIsGliding = false;
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Glide End"));

            // Restore default aerial control and gravity
            GetCharacterMovement()->AirControl = DefaultAirControl;
            GetCharacterMovement()->GravityScale = DefaultGravity;
        }
    }
}

bool ACharacterCrow::CanUseGlideAbility() const
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    return !bIsGliding && (CurrentTime - LastUsedSpell02Time >= ScarecrowBreezeCD);
}

void ACharacterCrow::Ultimate_Implementation()
{
    // Verify if the ability is available
    const float CurrentTime = GetWorld()->GetTimeSeconds();

    if (CurrentTime - LastUsedUltimateTime >= UltimateCD)
    {
        LastUsedUltimateTime = CurrentTime;

        // Get the player controller from the world
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

        if (PlayerController)
        {
            // Get the camera forward vector from the player controller
            FVector CameraForwardVector = PlayerController->GetControlRotation().Vector();

            // Define the target location (center of the screen)
            FVector TargetLocation = GetActorLocation() + CameraForwardVector * 1000.0f;

            // Create a spline curve from the character to the right
            SetupCurvedMovement(TargetLocation);

            // Draw debug sphere at the end of the spline
            FVector SplineEndLocation = CurvedMovementSpline->GetLocationAtSplinePoint(CurvedMovementSpline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
            DrawDebugSphere(GetWorld(), SplineEndLocation, 50.0f, 32, FColor::Orange, false, 2.0f, 0, 1.0f);

            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Curved Movement Ability Activated"));
        }
        else
        {
            // Handle the case where the player controller is not found
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Error: Player Controller not found"));
        }
    }
}

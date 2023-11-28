// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Vivianne/Cauldron.h"

// Sets default values
ACauldron::ACauldron()
{
    // Set this actor to call Tick() every frame. 
    PrimaryActorTick.bCanEverTick = true;

    // Initialize your cauldron's mesh component here
    cauldronMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CauldronMesh"));

    HitboxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitboxComponent"));
    HitboxComponent->SetupAttachment(cauldronMesh);
    
    
    // Initialize the flag
    bRotationCorrected = false;
}

// Called when the game starts or when spawned
void ACauldron::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(15.f);

    HitboxComponent->SetBoxExtent(FVector(5, 2, 5)); // Set the size of the hitbox
    HitboxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // Set an appropriate collision profile
    HitboxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACauldron::OnHitboxOverlapBegin);

    
}

// Called every frame
void ACauldron::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // If the cauldron has been thrown and is not yet corrected
    if (!bRotationCorrected)
    {
        if (FMath::IsNearlyZero(GetVelocity().Z, 0.f) && FMath::IsNearlyZero(GetVelocity().X, 0.f) && FMath::IsNearlyZero(GetVelocity().Y, 0.f))
        {
            // Schedule a rotation correction very soon after it stops moving vertically
            if (!(GetActorRotation() == FRotator::ZeroRotator))
            {
                CorrectRotation();
            }


        }
    }

}

void ACauldron::CorrectRotation()
{
    // Get the world's up vector
    FVector WorldUpVector = FVector::UpVector;

    // Get the cauldron's up vector
    FVector CauldronUpVector = GetActorUpVector();

    // If the cauldron is upside down or on its side, we want to apply torque to correct it
    if (!CauldronUpVector.Equals(WorldUpVector, 0.6f)) // 0.1f is a small tolerance for what we consider "upright"
    {
        // Set the cauldron's rotation to be upright
        SetActorRotation(FRotator::ZeroRotator);

        bRotationCorrected = true;
    }




}

void ACauldron::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("t'es dedans connard"));
}

// Fill out your copyright notice in the Description page of Project Settings.



#include "Characters/Vivianne/PotionPuddle.h"

// Sets default values
APotionPuddle::APotionPuddle()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    puddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuddleMesh"));

    HealNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HealNiagara"));
    PoisonNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PoisonNiagara"));

    HealNiagara->SetupAttachment(puddleMesh);
    HealNiagara->SetAutoActivate(false);

    PoisonNiagara->SetupAttachment(puddleMesh);
    PoisonNiagara->SetAutoActivate(false);

    puddleTimer = 0.5f;

}

void APotionPuddle::setHealing(bool healingP)
{
    healing = healingP;
    if (healing)
    {
        HealNiagara->Activate(true);
        PoisonNiagara->Deactivate();
    }
    else
    {
        PoisonNiagara->Activate(true);
        HealNiagara->Deactivate();
    }
}

void APotionPuddle::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (healing)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("healing player"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("damaging player"));
        // Handle poison
    }
    
}

// Called when the game starts or when spawned
void APotionPuddle::BeginPlay()
{
    Super::BeginPlay();
    puddleMesh->OnComponentBeginOverlap.AddDynamic(this, &APotionPuddle::OnOverlap);


}

// Called every frame
void APotionPuddle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    puddleTimer -= DeltaTime;
    if (puddleTimer < 0.f)
    {
        Destroy();
    }

}
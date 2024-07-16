#include "ActorsComponents/HA_FireBallComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Weapons/HA_FireBall.h"

UHA_FireBallComponent::UHA_FireBallComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHA_FireBallComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UHA_FireBallComponent::ShootFireBall(FTransform& Transform)
{
    if (!FireBallClass) return;
    if (!GetOwner()) return;
    if (LiveFireBalls.Num() >= MaxFireBalls) return;
    
    AHA_FireBall* FireBall = GetWorld()->SpawnActorDeferred<AHA_FireBall>(FireBallClass, Transform);
    if (!FireBall) return;
    
    if (FireBallSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireBallSound, GetOwner()->GetActorLocation());
    }

    FireBallsLastIndex++;
    FireBall->FireBallIndex = FireBallsLastIndex;
    FireBall->FireballDestroyedDelegate.AddLambda([this, FireBall]()
    {
        // Removing from the map when get destroyed
        LiveFireBalls.Remove(FireBall->FireBallIndex);
        // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Removed FireBalls: %d - Last index: %d"), LiveFireBalls.Num(), FireBallsLastIndex));
        if (LiveFireBalls.Num() == 0) FireBallsLastIndex = 0;
    });
    
    UGameplayStatics::FinishSpawningActor(FireBall, Transform);
    LiveFireBalls.Add(FireBallsLastIndex, FireBall);
    // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Removed FireBalls: %d - Last index: %d"), LiveFireBalls.Num(), FireBallsLastIndex));
}


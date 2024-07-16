// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_Coin.h"

#include "Kismet/GameplayStatics.h"

void AHA_Block_Coin::BeginPlay()
{
	Super::BeginPlay();
}

void AHA_Block_Coin::MoveMeshFromTimelineFloat(float InValueLocation, float InValueRotation)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += InValueLocation;
	SetActorLocation(NewLocation);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += InValueRotation;
	SetActorRotation(NewRotation);
}

void AHA_Block_Coin::ShowCoinEffectAndDestroy(UParticleSystem* CoinEffect)
{
	if (!CoinEffect) return;

	UGameplayStatics::SpawnEmitterAtLocation(this, CoinEffect, Mesh->GetComponentLocation());
	Destroy();
}

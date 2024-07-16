// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "HA_Block_Coin.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Block_Coin : public AHA_BaseActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void MoveMeshFromTimelineFloat(float InValueLocation, float InValueRotation);
	void ShowCoinEffectAndDestroy(UParticleSystem* CoinEffect);
	
};

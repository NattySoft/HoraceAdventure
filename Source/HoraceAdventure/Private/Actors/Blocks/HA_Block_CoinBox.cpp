// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_CoinBox.h"

#include "Kismet/GameplayStatics.h"

void AHA_Block_CoinBox::TimerStart()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHA_Block_CoinBox::TimerExpired, TimerAmount);
}

void AHA_Block_CoinBox::TimerExpired()
{
	HasTimerExpired = true;
}

void AHA_Block_CoinBox::HitBlock()
{
	Super::HitBlock();

	if (!bFinishedInteracting)
	{
		if (!HasTimerExpired && !TimerHandle.IsValid())
		{
			// Start the timer, if not started yet, to stop the interaction when expires
			TimerStart();
		}

		// Play sounds
		PlaySoundEffect();
		
		// Show the effects
		ShowEffects();

		// Spawn points widget
		ShowPointsWidget(GetActorTransform());

		// Spawn a coin actor
		SpawnCoinActor();
	
		// Add points to the player
		AddPointsToPlayer();

		// Shake the block
		ShakeBlock();
		
		if (HasTimerExpired)
		{
			// Change the material
			SwapMaterial();
	
			// This will make sure that the following logic will be run once
			bFinishedInteracting = true;
		}
	}
	else
	{
		PlayInactiveSoundEffect();
		
	}
}

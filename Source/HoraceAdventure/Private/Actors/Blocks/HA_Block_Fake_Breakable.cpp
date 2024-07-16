// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_Fake_Breakable.h"

#include "HoraceAdventure/HoraceAdventure.h"
#include "Kismet/GameplayStatics.h"

AHA_Block_Fake_Breakable::AHA_Block_Fake_Breakable()
{
	Tags.Add(PBlockTag);
}

void AHA_Block_Fake_Breakable::HitBlock()
{
	Super::HitBlock();

	if (!bFinishedInteracting)
	{
		// This will make sure that the following logic will be run once
		bFinishedInteracting = true;

		// Play sounds
		PlaySoundEffect();
		
		// Show the effects
		ShowEffects();

		// Change the material
		SwapMaterial();
	
		// Spawn points widget
		ShowPointsWidget(GetActorTransform());

		// Spawn a coin actor
		SpawnCoinActor();
	
		// Add points to the player
		AddPointsToPlayer();

		// Shake the block
		ShakeBlock();
	}
	else
	{
		PlayInactiveSoundEffect();
		
	}
	
	
	// Destroy the actor
	// Destroy();
	
}

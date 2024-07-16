// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_Breackable.h"

#include "Characters/HA_Horace.h"
#include "HoraceAdventure/HoraceAdventure.h"

AHA_BlockBreackable::AHA_BlockBreackable()
{
	Tags.Add(PBlockTag);
}

void AHA_BlockBreackable::HitBlock()
{
	if (Horace->GetHitPoints() >= EHP_Big)
	{
		Super::HitBlock();

		// Play sounds
		PlaySoundEffect();
	
		// Show the effects
		ShowEffects();

		// Spawn points widget
		ShowPointsWidget(GetActorTransform());

		// Add points to the player
		AddPointsToPlayer();

		// Destroy the actor
		Destroy();
	}
	else
	{
		// Play sounds
		PlayInactiveSoundEffect();
		
		// Shake the block
		ShakeBlock();
	}
	
}

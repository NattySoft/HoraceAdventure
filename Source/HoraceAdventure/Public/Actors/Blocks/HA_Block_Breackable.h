// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/Blocks/HA_Block_Base.h"
#include "HA_Block_Breackable.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_BlockBreackable : public AHA_BlockBase
{
	GENERATED_BODY()

public:
	AHA_BlockBreackable();
	virtual void HitBlock() override;
};

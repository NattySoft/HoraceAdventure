// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/Blocks/HA_Block_Base.h"
#include "HA_Block_Fake_Breakable.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Block_Fake_Breakable : public AHA_BlockBase
{
	GENERATED_BODY()

public:
	AHA_Block_Fake_Breakable();
	virtual void HitBlock() override;
	
};

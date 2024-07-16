// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlatformerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlatformerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORACEADVENTURE_API IPlatformerInterface
{
	GENERATED_BODY()

public:
	virtual void HitBlock();
};

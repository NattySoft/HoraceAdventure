// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HA_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API UHA_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	int32 Coins = 0;
	int32 Lives = 3;
	int32 Points = 0;
	
};

// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/Blocks/HA_Block_Base.h"
#include "HA_Block_CoinBox.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Block_CoinBox : public AHA_BlockBase
{
	GENERATED_BODY()

private:
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float TimerAmount = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool HasTimerExpired = false;
	
	UFUNCTION()
	void TimerExpired();
	void TimerStart();
	
public:
	virtual void HitBlock() override;
};

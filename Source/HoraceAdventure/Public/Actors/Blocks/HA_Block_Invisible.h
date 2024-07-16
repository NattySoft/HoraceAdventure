// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/Blocks/HA_Block_Base.h"
#include "HA_Block_Invisible.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Block_Invisible : public AHA_BlockBase
{
	GENERATED_BODY()

public:
	AHA_Block_Invisible();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Box;

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void HitBlock() override;
};

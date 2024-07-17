// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_InstantDeath.generated.h"

class UBoxComponent;

UCLASS()
class HORACEADVENTURE_API AHA_InstantDeath : public AActor
{
	GENERATED_BODY()
	
public:	
	AHA_InstantDeath();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category="InstantDeath")
	UBoxComponent* Box;
};

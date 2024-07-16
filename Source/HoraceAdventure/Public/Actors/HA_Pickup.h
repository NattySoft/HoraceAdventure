// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "HA_Pickup.generated.h"

class UParticleEmitter;
class USphereComponent;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Pickup : public AHA_BaseActor
{
	GENERATED_BODY()

public:
	AHA_Pickup();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* PickupEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinsValue = 1;
	
private:
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};

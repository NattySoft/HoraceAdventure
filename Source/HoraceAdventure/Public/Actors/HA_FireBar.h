// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "HA_FireBar.generated.h"

class URotatingMovementComponent;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_FireBar : public AHA_BaseActor
{
	GENERATED_BODY()

public:
	AHA_FireBar();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* Ball;

	UPROPERTY(EditAnywhere)
	URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere, Category="Bar Customisation")
	int32 FlameBallNumber = 5;

	UPROPERTY(EditAnywhere, Category="Bar Customisation")
	int32 FlameBallDistanceApart = 60;

	UPROPERTY(EditAnywhere, Category="Bar Customisation")
	FVector FlameBallSize = FVector(0.5);

	UPROPERTY(EditAnywhere, Category="Bar Customisation")
	FRotator RotationRate = FRotator(50.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category="Hit Customisation")
	int32 HitPointAdjustmentToPlayer = -1;

	UPROPERTY(EditAnywhere, Category="Hit Customisation")
	FVector PlayerHitVelocity = FVector(0.f, 0.f, 500.f);

	UPROPERTY(EditAnywhere, Category="Hit Customisation")
	float HitCooldown = 1.f;

private:
	bool bBoxHit = false;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ResetBoxHit();
};

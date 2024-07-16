// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/Blocks/HA_Block_Base.h"
#include "HA_Block_FireFlower.generated.h"

class UArrowComponent;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Block_FireFlower : public AHA_BlockBase
{
	GENERATED_BODY()

public:
	AHA_Block_FireFlower();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxFlower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshFlower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* GlowingVFX_Particle;

	UPROPERTY()
	UParticleSystemComponent* PowerUpGlow;
	
	void GlowBlock();

	UFUNCTION()
	void OnBoxFlowerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// ######### MOVING FLOWER UP ##########
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	UCurveFloat* FlowerMovingCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float FlowerTimeLineTickTime = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float FlowerTimeLinePlayRate = 1.f;
	
	FTimeline FlowerMovingTimeline;
	FTimerHandle FlowerTimeLineTimerHandle;
	
	UFUNCTION()
	void FlowerTickTimeline();
	
	UFUNCTION()
	void FlowerMovingUpdate(float Alpha);
	void FlowerStartMoving();
	void FlowerMove();
	// ######### END MOVING FLOWER UP ##########
	
public:
	virtual void HitBlock() override;

	
};

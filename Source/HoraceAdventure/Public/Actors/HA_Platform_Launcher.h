// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "Components/TimelineComponent.h"
#include "HA_Platform_Launcher.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Platform_Launcher : public AHA_BaseActor
{
	GENERATED_BODY()

public:
	AHA_Platform_Launcher();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInstancedStaticMeshComponent* MushTruck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MushTopScaleX = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MushTopScaleY = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MushTopScaleZ = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LaunchVelocity = FVector(0.f, 0.f, 2500.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MakeEditWidget="true"))
	FVector TrunkEndPoint = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* EmitterParticleWhenHit;
	
private:
	UFUNCTION()
	void OnCollisionBottomEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnCollisionBottomStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// ######### MOVING TIMELINE #############
	UFUNCTION()
	void ResetTimeLine();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline", meta=(AllowPrivateAccess="true"))
	float TimeLineTickTime = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline", meta=(AllowPrivateAccess="true"))
	float TimeLinePlayRate = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline", meta=(AllowPrivateAccess="true"))
	UCurveFloat* MovingCurve = nullptr;
	FTimeline MovingTimeline;
	FTimerHandle TimeLineTimerHandle;
	FTimerHandle TimeLineResetTimerHandle;
	
	UFUNCTION()
	void MeshTickTimeline();
	
	UFUNCTION()
	void MeshMovingUpdate(float Alpha);
	void MeshStartMoving();
	// ######### END MOVING TIMELINE #############
};

// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "HA_GrowingComponent.generated.h"


class AHA_Horace;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORACEADVENTURE_API UHA_GrowingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHA_GrowingComponent();
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AHA_Horace* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds")
	USoundBase* GrowingSound;
	
	// ######### TIMELINE ##########
	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	UCurveFloat* MovingCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float TimeLineTickTime = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float TimeLinePlayRate = 1.f;
	
	FTimeline MovingTimeline;
	FTimerHandle TimeLineTimerHandle;
	
	UFUNCTION()
	void TickTimeline();
	
	UFUNCTION()
	void MovingUpdate(float Alpha);
	void BeginTimeline();
	void ReverseTimeline();
	// ######### END TIMELINE ##########

private:
	float CapsuleForwardHalfHeight = 120.f;
	float CapsuleForwardRadius = 40.f;
	float MeshForwardLocationZ = -90.f;
	
	float CapsuleOrigHalfHeight;
	float CapsuleOrigRadius;
	float MeshOrigLocationZ;
	
public:	
	void Start();
	void Reverse();
};

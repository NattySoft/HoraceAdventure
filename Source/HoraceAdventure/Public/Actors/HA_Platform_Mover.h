// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_Platform_Actor.h"
#include "Components/TimelineComponent.h"
#include "HA_Platform_Mover.generated.h"


/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Platform_Mover : public AHA_Platform_Actor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loction Points", meta=(MakeEditWidget="true"))
	FVector LocStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loction Points", meta=(MakeEditWidget="true"))
	FVector LocEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	UCurveFloat* MovingCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float TimeLineTickTime = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float TimeLinePlayRate = 1.f;
	
private:
	FTimeline MovingTimeline;
	FTimerHandle TimeLineTimerHandle;
	
	UFUNCTION()
	void TickTimeline();
	
	UFUNCTION()
	void MovingUpdate(float Alpha);
	void StartMoving();
};

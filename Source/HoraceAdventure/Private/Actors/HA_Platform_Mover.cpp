// NattySoft - All Right Reserved


#include "Actors/HA_Platform_Mover.h"

#include "Kismet/KismetMathLibrary.h"

void AHA_Platform_Mover::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, "MovingUpdate");

	check(MovingCurve);
	MovingTimeline.SetLooping(true);
	MovingTimeline.AddInterpFloat(MovingCurve, ProgressUpdate);
	StartMoving();
	GetWorldTimerManager().SetTimer(TimeLineTimerHandle, this, &AHA_Platform_Mover::TickTimeline, TimeLineTickTime, true, 0.0f);
}

void AHA_Platform_Mover::TickTimeline()
{
	if (MovingTimeline.IsPlaying())
	{
		MovingTimeline.TickTimeline(TimeLineTickTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimeLineTimerHandle);
	}
}

void AHA_Platform_Mover::MovingUpdate(float Alpha)
{
	FVector NewPosition = UKismetMathLibrary::VLerp(LocStart, LocEnd, Alpha);
	Mesh->SetRelativeLocation(NewPosition);
}

void AHA_Platform_Mover::StartMoving()
{
	MovingTimeline.SetPlayRate(TimeLinePlayRate);
	MovingTimeline.Play();
}

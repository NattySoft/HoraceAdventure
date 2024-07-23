// NattySoft - All Right Reserved


#include "ActorsComponents/HA_GrowingComponent.h"
#include "Characters/HA_Horace.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

UHA_GrowingComponent::UHA_GrowingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHA_GrowingComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHA_Horace>(GetOwner());
	checkf(Player, TEXT("Player not set as owner"));

	// Storing original values
	CapsuleOrigHalfHeight = Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	CapsuleOrigRadius = Player->GetCapsuleComponent()->GetScaledCapsuleRadius();
	MeshOrigLocationZ = Player->GetMesh()->GetRelativeLocation().Z;
	Player->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleOrigHalfHeight);
	Player->GetCapsuleComponent()->SetCapsuleRadius(CapsuleOrigRadius);
	Player->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, MeshOrigLocationZ));
	
	if (MovingCurve)
	{
		
		FOnTimelineFloat ProgressUpdate;
		ProgressUpdate.BindUFunction(this, "MovingUpdate");
		MovingTimeline.SetLooping(false);
		MovingTimeline.AddInterpFloat(MovingCurve, ProgressUpdate);
		MovingTimeline.SetPlayRate(TimeLinePlayRate);

		MovingTimeline.SetPropertySetObject(this); // Object to set the property on
		MovingTimeline.SetDirectionPropertyName(FName("TimelineDirection")); // Name of the UPROPERTY

	}
}

void UHA_GrowingComponent::TickTimeline()
{
	if (MovingTimeline.IsPlaying())
	{
		MovingTimeline.TickTimeline(TimeLineTickTime);
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(this, 1.f);
		if (TimelineDirection == ETimelineDirection::Forward)
		{
			Player->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleForwardHalfHeight);
			Player->GetCapsuleComponent()->SetCapsuleRadius(CapsuleForwardRadius);
			Player->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, MeshForwardLocationZ));
		}
		else
		{
			Player->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleOrigHalfHeight);
			Player->GetCapsuleComponent()->SetCapsuleRadius(CapsuleOrigRadius);
			Player->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, MeshOrigLocationZ));
		}
		
		GetWorld()->GetTimerManager().ClearTimer(TimeLineTimerHandle);
	}
}

void UHA_GrowingComponent::MovingUpdate(const float Alpha)
{
	if (!IsValid(Player)) return;

	const FVector NewScale = Player->GetPlayerScaleSmall() * Alpha;
	Player->GetMesh()->SetRelativeScale3D(NewScale);
}

void UHA_GrowingComponent::BeginTimeline()
{
	MovingTimeline.PlayFromStart();
}

void UHA_GrowingComponent::ReverseTimeline()
{
	MovingTimeline.ReverseFromEnd();
}

void UHA_GrowingComponent::Start()
{
	if (!IsValid(Player)) return;

	UGameplayStatics::SetGlobalTimeDilation(GetOwner(), .8f);
	Player->SetHasFireFlower(true);
	
	// Play the sound
	if (GrowingSound)
	{
		UGameplayStatics::PlaySound2D(Player, GrowingSound);
	}

	// Adjust hit points
	Player->AdjustHitPoints(1);

	BeginTimeline();
	TimeLineTimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(TimeLineTimerHandle, this, &UHA_GrowingComponent::TickTimeline, TimeLineTickTime, true, 0.0f);	
}

void UHA_GrowingComponent::Reverse()
{
	if (!IsValid(Player)) return;

	Player->SetHasFireFlower(false);
	ReverseTimeline();
	TimeLineTimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(TimeLineTimerHandle, this, &UHA_GrowingComponent::TickTimeline, TimeLineTickTime, true, 0.0f);	
}

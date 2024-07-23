// NattySoft - All Right Reserved


#include "Actors/CheckPoints/HA_CheckPointBase.h"

#include "Characters/HA_Horace.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/FunctionsLibrary.h"

AHA_CheckPointBase::AHA_CheckPointBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	RespawnTransform = CreateDefaultSubobject<UArrowComponent>("RespawnTransform");
	FlagPivotPoint = CreateDefaultSubobject<UStaticMeshComponent>("FlagPivotPoint");
	FlagBase = CreateDefaultSubobject<UStaticMeshComponent>("FlagBase");
	Flag = CreateDefaultSubobject<UStaticMeshComponent>("Flag");
	FlagArm = CreateDefaultSubobject<UStaticMeshComponent>("FlagArm");

	SetRootComponent(SceneComponent);
	Box->SetupAttachment(SceneComponent);
	RespawnTransform->SetupAttachment(Box);
	FlagPivotPoint->SetupAttachment(Box);
	FlagBase->SetupAttachment(Box);
	FlagArm->SetupAttachment(Box);
	Flag->SetupAttachment(FlagArm);

	Box->SetBoxExtent(FVector(200.f, 200.f, 500.f));
	Box->SetLineThickness(5.f);
	Box->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	Box->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	FlagPivotPoint->SetRelativeScale3D(FVector(.5f));
	FlagPivotPoint->SetRelativeLocation(FVector(-200.f, 0.f, -400.f));

	FlagBase->SetRelativeScale3D(FVector(.5f, 2.f, 2.f));
	FlagBase->SetRelativeLocation(FVector(-200.f, 0.f, -500.f));

	FlagArm->SetRelativeScale3D(FVector(.5f, 1.f, 1.f));
	FlagArm->SetRelativeLocation(FVector(-205.f, 0.f, -390.f));
	FlagArm->SetRelativeRotation(FlagArmRotateStart);

	Flag->SetRelativeLocation(FVector(10.f, -10.f, 350.f));
	Flag->SetRelativeScale3D(FVector(.2f, 1.f, 2.f));
	Flag->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	RespawnTransform->SetRelativeLocation(FVector(0.f, 0.f, -400.f));
	RespawnTransform->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AHA_CheckPointBase::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AHA_CheckPointBase::OnBoxBeginOverlap);

	FOnTimelineFloat CheckPointProgressUpdate;
	CheckPointProgressUpdate.BindUFunction(this, "CheckPointMovingUpdate");

	checkf(CheckPointMovingCurve, TEXT("CheckPoint moving curve not defined"));
	CheckPointMovingTimeline.SetLooping(false);
	CheckPointMovingTimeline.AddInterpFloat(CheckPointMovingCurve, CheckPointProgressUpdate);
}

void AHA_CheckPointBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bFlagArmRotated) return;

	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	bFlagArmRotated = true;
	Horace->SetNextSpawnLocation(RespawnTransform->GetComponentTransform());
	CheckPointMove();
}

void AHA_CheckPointBase::CheckPointTickTimeline()
{
	if (CheckPointMovingTimeline.IsPlaying())
	{
		CheckPointMovingTimeline.TickTimeline(CheckPointTimeLineTickTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CheckPointTimeLineTimerHandle);
		
		UFunctionsLibrary::PlaySoundFx(this, CheckPointSound);
		FVector SpawnLocation = RespawnTransform->GetComponentLocation();
		SpawnLocation.Z += 200.f;
		UFunctionsLibrary::PlayInteractFx(this, CheckPointEffect, nullptr, SpawnLocation, FVector(10.f));
	}
}

void AHA_CheckPointBase::CheckPointMovingUpdate(float Alpha) const
{
	FRotator TargetRotation = UKismetMathLibrary::RLerp(
		FlagArmRotateStart,
		FlagArmRotateEnd,
		Alpha,
		false
	);
	FlagArm->SetRelativeRotation(TargetRotation);
}

void AHA_CheckPointBase::CheckPointStartMoving()
{
	CheckPointMovingTimeline.SetPlayRate(CheckPointTimeLinePlayRate);
	CheckPointMovingTimeline.PlayFromStart();

	// FTimerHandle PlayCheckPointSoundHandler;
	// constexpr float PlayCheckPointDelay = 0.2f;
	// GetWorldTimerManager().SetTimer(PlayCheckPointSoundHandler, this, &AHA_CheckPointBase::PlayWarpSound, PlayCheckPointDelay);
}

void AHA_CheckPointBase::CheckPointMove()
{
	CheckPointStartMoving();
	GetWorldTimerManager().SetTimer(CheckPointTimeLineTimerHandle, this, &AHA_CheckPointBase::CheckPointTickTimeline, CheckPointTimeLineTickTime, true, 0.0f);
}



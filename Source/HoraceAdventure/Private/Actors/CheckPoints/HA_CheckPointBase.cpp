// NattySoft - All Right Reserved


#include "Actors/CheckPoints/HA_CheckPointBase.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

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
	FlagArm->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	Flag->SetRelativeLocation(FVector(10.f, -10.f, 350.f));
	Flag->SetRelativeScale3D(FVector(.2f, 1.f, 2.f));
	Flag->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	RespawnTransform->SetRelativeLocation(FVector(0.f, 0.f, -400.f));
	RespawnTransform->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AHA_CheckPointBase::BeginPlay()
{
	Super::BeginPlay();
	
}



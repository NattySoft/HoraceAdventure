// NattySoft - All Right Reserved


#include "Actors/CheckPoints/HA_EndOfLevelFlag.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

AHA_EndOfLevelFlag::AHA_EndOfLevelFlag()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerVolume");
	Flag = CreateDefaultSubobject<UStaticMeshComponent>("Flag");
	FlagPole = CreateDefaultSubobject<UStaticMeshComponent>("FlagPole");
	FlagBase = CreateDefaultSubobject<UStaticMeshComponent>("FlagBase");
	FlagTop = CreateDefaultSubobject<UStaticMeshComponent>("FlagTop");
	FlagEndPoint = CreateDefaultSubobject<UBillboardComponent>("FlagEndPoint");
	FireworksArea = CreateDefaultSubobject<UBoxComponent>("FireworksArea");
	PlayerEndPoint = CreateDefaultSubobject<UArrowComponent>("PlayerEndPoint");
	PlayerExplodePoint = CreateDefaultSubobject<UArrowComponent>("PlayerExplodePoint");
	PlayerStartPoint = CreateDefaultSubobject<UArrowComponent>("PlayerStartPoint");

	SetRootComponent(SceneComponent);
	TriggerVolume->SetupAttachment(SceneComponent);
	Flag->SetupAttachment(SceneComponent);
	FlagPole->SetupAttachment(SceneComponent);
	FlagBase->SetupAttachment(SceneComponent);
	FlagTop->SetupAttachment(SceneComponent);
	FlagEndPoint->SetupAttachment(SceneComponent);
	FireworksArea->SetupAttachment(SceneComponent);
	PlayerEndPoint->SetupAttachment(SceneComponent);
	PlayerExplodePoint->SetupAttachment(SceneComponent);
	PlayerStartPoint->SetupAttachment(SceneComponent);

	Flag->SetRelativeLocation(FVector(85.f, 0.f, 845.f));
	Flag->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	Flag->SetRelativeScale3D(FVector(1.5f, 1.f, 1.f));
	
	FlagPole->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	FlagPole->SetRelativeScale3D(FVector(.2f, .2f, 8.f));

	FlagBase->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	
	FlagTop->SetRelativeLocation(FVector(0.f, 0.f, 895.f));
	FlagTop->SetRelativeScale3D(FVector(.5f));

	FlagEndPoint->SetRelativeLocation(FVector(85.f, 0.f, 150.f));
	FlagEndPoint->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	FireworksArea->SetRelativeLocation(FVector(850.f, 0.f, 700.f));
	FireworksArea->SetBoxExtent(FVector(500.f, 200.f, 300.f));
	FireworksArea->SetLineThickness(5.f);
	FireworksArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PlayerEndPoint->SetRelativeLocation(FVector(-25.f, 30.f, 190.f));
	PlayerExplodePoint->SetRelativeLocation(FVector(850.f, 0.f, 500.f));
	PlayerStartPoint->SetRelativeLocation(FVector(-25.f, 30.f, 845.f));

	TriggerVolume->SetRelativeLocation(FVector(5.f, 0.f, 1000.f));
	TriggerVolume->SetBoxExtent(FVector(32.f, 200.f, 1000.f));
	TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void AHA_EndOfLevelFlag::BeginPlay()
{
	Super::BeginPlay();
	
}

// NattySoft - All Right Reserved


#include "Actors/Pipes/HA_WarpPipe.h"

#include "Characters/HA_Horace.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_WarpPipe::AHA_WarpPipe()
{
	PipeBody = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Pipe Body");
	PipeBody->SetupAttachment(GetRootComponent());

	PipeInside = CreateDefaultSubobject<UStaticMeshComponent>("Pipe Inside");
	PipeInside->SetupAttachment(Mesh);

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Collision->SetupAttachment(Mesh);

	WarpInPoint = CreateDefaultSubobject<UBillboardComponent>("Warp In Point");
	WarpInPoint->SetupAttachment(GetRootComponent());

	WarpOutPoint = CreateDefaultSubobject<UBillboardComponent>("Warp Out Point");
	WarpOutPoint->SetupAttachment(GetRootComponent());

	PipeBody->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	PipeBody->SetRelativeScale3D(FVector(2.25f, 2.25f, 1.f));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 35.f));
	Mesh->SetRelativeScale3D(FVector(2.75f, 2.75f, .5f));

	PipeInside->SetRelativeLocation(FVector(0.f, 0.f, 25.5f));
	PipeInside->SetRelativeScale3D(FVector(.8f, .8f, .5f));

	Collision->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	Collision->SetCapsuleHalfHeight(300.f);
	Collision->SetCapsuleRadius(40.f);

	Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WarpInPoint->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	WarpOutPoint->SetRelativeLocation(FVector(0.f, 0.f, -35.f));
	
}

void AHA_WarpPipe::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHA_WarpPipe::OnCollisionBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AHA_WarpPipe::OnCollisionEndOverlap);

	FOnTimelineFloat PipeProgressUpdate;
	PipeProgressUpdate.BindUFunction(this, "PipeMovingUpdate");

	checkf(PipeMovingCurve, TEXT("Pipe moving curve not defined"));
	PipeMovingTimeline.SetLooping(false);
	PipeMovingTimeline.AddInterpFloat(PipeMovingCurve, PipeProgressUpdate);

}

void AHA_WarpPipe::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const float TruckEndPointLength = PipeEndPoint.Length();
	const int32 TrunkEndPointLastIndex = FMath::TruncToInt(TruckEndPointLength / 100.f);

	PipeBody->ClearInstances();
	for (int i = 0; i < TrunkEndPointLastIndex; i++)
	{
		FVector MushLocation = FVector::ZeroVector;
		MushLocation.Z = static_cast<float>(i * -100);
		FTransform AddPosition = FTransform();
		AddPosition.SetLocation(MushLocation);
		PipeBody->AddInstance(AddPosition);
	}
	
}

void AHA_WarpPipe::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	Horace->SetOverlappingPipe(this);
	bIsGateOpen = true;
}

void AHA_WarpPipe::OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	Horace->SetOverlappingPipe(nullptr);
	bIsGateOpen = false;
}

void AHA_WarpPipe::Interact(AHA_Horace* InHorace)
{
	if (!IsValid(InHorace)) return;
	HoraceRef = InHorace;
	MovePlayerUp();
	MovePlayerDown();
}

void AHA_WarpPipe::MovePlayerUp()
{
	if (!bCanInteract) return;
	if (bIsDownPipe) return;
	if (!IsValid(HoraceRef)) return;
	
	AHA_PlayerController* PlayerController = HoraceRef->GetHoraceController();
	PlayerController->DisableInput(PlayerController);
	PipeMove();
}

void AHA_WarpPipe::MovePlayerDown()
{
	if (!bCanInteract) return;
	if (!bIsDownPipe) return;
	if (!IsValid(HoraceRef)) return;
	
	AHA_PlayerController* PlayerController = HoraceRef->GetHoraceController();
	PlayerController->DisableInput(PlayerController);
	PipeMove();
}

void AHA_WarpPipe::PipeTickTimeline()
{
	if (PipeMovingTimeline.IsPlaying())
	{
		PipeMovingTimeline.TickTimeline(PipeTimeLineTickTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(PipeTimeLineTimerHandle);

		if (!bIsExiting)
		{
			FTimerHandle PlayPipeSoundHandler;
			constexpr float PlayPipeDelay = 1.f;
			GetWorldTimerManager().SetTimer(PlayPipeSoundHandler, this, &AHA_WarpPipe::PlayExit, PlayPipeDelay);
		}
		
		AHA_PlayerController* PlayerController = HoraceRef->GetHoraceController();
		PlayerController->EnableInput(PlayerController);
	}
}

void AHA_WarpPipe::PipeMovingUpdate(const float Alpha) const
{
	// if (!IsValid(BoxPipe)) return;
	if (!IsValid(HoraceRef)) return;

	FVector WarpLocation;
	float MovementAlpha = bIsDownPipe ? -1 * Alpha : Alpha;

	if (bIsExiting)
	{
		WarpLocation = WarpToLocale;
		MovementAlpha = bIsExitingRaisingUp ? Alpha : -1 * Alpha;
		// UFunctionsLibrary::PrintDebugMessage(FString::Printf(TEXT("MovementAlpha: %f"), MovementAlpha));
	}
	else
	{
		WarpLocation = WarpInPoint->GetComponentLocation();
	}

	WarpLocation.Z += MovementAlpha;
	HoraceRef->GetCapsuleComponent()->SetRelativeLocation(WarpLocation);
	HoraceRef->GetCapsuleComponent()->SetRelativeRotation(FRotator::ZeroRotator);

}

void AHA_WarpPipe::PipeStartMoving()
{
	PipeMovingTimeline.SetPlayRate(PipeTimeLinePlayRate);
	PipeMovingTimeline.PlayFromStart();

	FTimerHandle PlayPipeSoundHandler;
	constexpr float PlayPipeDelay = 0.2f;
	GetWorldTimerManager().SetTimer(PlayPipeSoundHandler, this, &AHA_WarpPipe::PlayWarpSound, PlayPipeDelay);
}

void AHA_WarpPipe::PipeMove()
{
	PipeStartMoving();
	GetWorldTimerManager().SetTimer(PipeTimeLineTimerHandle, this, &AHA_WarpPipe::PipeTickTimeline, PipeTimeLineTickTime, true, 0.0f);
}

void AHA_WarpPipe::PlayWarpSound() const
{
	if (WarpSound)
	{
		// UFunctionsLibrary::PrintDebugMessage("AHA_WarpPipe::PlayWarpSound");
		UGameplayStatics::PlaySound2D(this, WarpSound);
	}
}

void AHA_WarpPipe::PlayExit()
{
	bIsExiting = true;
	PipeMove();
}


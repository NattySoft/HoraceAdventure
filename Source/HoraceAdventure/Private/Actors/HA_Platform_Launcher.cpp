// NattySoft - All Right Reserved


#include "Actors/HA_Platform_Launcher.h"

#include "Characters/HA_Horace.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_Platform_Launcher::AHA_Platform_Launcher()
{
	MushTruck = CreateDefaultSubobject<UInstancedStaticMeshComponent>("MushTruck");
	CollisionBottom = CreateDefaultSubobject<UBoxComponent>("CollisionBottom");

	MushTruck->SetupAttachment(GetRootComponent());
	Mesh->SetupAttachment(GetRootComponent());
	CollisionBottom->SetupAttachment(Mesh);

	CollisionBottom->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBottom->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AHA_Platform_Launcher::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionBottom)
	{
		CollisionBottom->OnComponentBeginOverlap.AddDynamic(this, &AHA_Platform_Launcher::OnCollisionBottomStartOverlap);
		CollisionBottom->OnComponentEndOverlap.AddDynamic(this, &AHA_Platform_Launcher::OnCollisionBottomEndOverlap);
	}

	if (Mesh)
	{
		Mesh->OnComponentHit.AddDynamic(this, &AHA_Platform_Launcher::OnMeshHit);
	}

	// MeshInitialiseMoving();
}

void AHA_Platform_Launcher::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Mesh->SetWorldScale3D(FVector(MushTopScaleX, MushTopScaleY, MushTopScaleZ));
	const float TruckEndPointLength = TrunkEndPoint.Length();
	const int32 TrunkEndPointLastIndex = FMath::TruncToInt(TruckEndPointLength / 100.f);

	MushTruck->ClearInstances();
	for (int i = 0; i < TrunkEndPointLastIndex; i++)
	{
		FVector MushLocation = FVector::ZeroVector;
		MushLocation.Z = static_cast<float>(i * -100);
		FTransform MushPosition = FTransform();
		MushPosition.SetLocation(MushLocation);
		MushTruck->AddInstance(MushPosition);
	}
}

void AHA_Platform_Launcher::OnCollisionBottomStartOverlap(UPrimitiveComponent* OverlappedComponent,
	ThisClass::Super::Super* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}

void AHA_Platform_Launcher::OnCollisionBottomEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                        ThisClass::Super::Super* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (!IsValid(OtherActor)) return;
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}
}

void AHA_Platform_Launcher::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsValid(OtherActor)) return;
	const bool bIsGoingDown = Hit.ImpactNormal == FVector(0.f, 0.f, -1.f);
	if (const AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor); Horace && bIsGoingDown)
	{
		Cast<UCharacterMovementComponent>(Horace->GetMovementComponent())->Launch(LaunchVelocity);

		if (EmitterParticleWhenHit)
		{
			UGameplayStatics::SpawnEmitterAtLocation(Horace, EmitterParticleWhenHit, Hit.ImpactPoint, FRotator::ZeroRotator, FVector(3.f));
		}

		if (MovingCurve)
		{
			MeshStartMoving();
		}
		
	}
}

void AHA_Platform_Launcher::MeshStartMoving()
{
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, "MeshMovingUpdate");
	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, "ResetTimeLine");
	
	MovingTimeline.SetLooping(false);
	MovingTimeline.AddInterpFloat(MovingCurve, ProgressUpdate);
	MovingTimeline.SetTimelineFinishedFunc(FinishedEvent);
	
	MovingTimeline.SetPlayRate(TimeLinePlayRate);
	MovingTimeline.PlayFromStart();
	GetWorldTimerManager().SetTimer(TimeLineTimerHandle, this, &AHA_Platform_Launcher::MeshTickTimeline, TimeLineTickTime, true, 0.0f);
	GetWorldTimerManager().SetTimer(TimeLineResetTimerHandle, this, &AHA_Platform_Launcher::MeshTickTimeline, 2.f, true, 0.0f);
	
}

void AHA_Platform_Launcher::ResetTimeLine()
{
	MovingTimeline.Stop();
	GetWorldTimerManager().ClearTimer(TimeLineTimerHandle);
	GetWorldTimerManager().ClearTimer(TimeLineResetTimerHandle);	
}

void AHA_Platform_Launcher::MeshTickTimeline()
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

void AHA_Platform_Launcher::MeshMovingUpdate(float Alpha)
{
	const float NewMushTopScaleX = MushTopScaleX * Alpha;
	const float NewMushTopScaleY = MushTopScaleY * Alpha;
	const float NewMushTopScaleZ = MushTopScaleZ * Alpha;
	const FVector NewMushScale = FVector(NewMushTopScaleX, NewMushTopScaleY, NewMushTopScaleZ);
	Mesh->SetRelativeScale3D(NewMushScale);
}
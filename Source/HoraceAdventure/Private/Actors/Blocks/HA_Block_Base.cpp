// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_Base.h"

#include "Actors/Blocks/HA_Block_Coin.h"
#include "Actors/HA_PointsActor.h"
#include "Characters/HA_Horace.h"
#include "Components/SphereComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_BlockBase::AHA_BlockBase()
{
	ChildActor = CreateDefaultSubobject<UChildActorComponent>("ChildActor");
	ChildActor->SetupAttachment(Mesh);
	
	ChildActorCollider = CreateDefaultSubobject<USphereComponent>("ChildActorCollider");
	ChildActorCollider->SetupAttachment(ChildActor);
	ChildActorCollider->SetSphereRadius(30.f);
}

void AHA_BlockBase::BeginPlay()
{
	Super::BeginPlay();

	Horace = UFunctionsLibrary::GetHorace(UGameplayStatics::GetPlayerCharacter(this, 0));
	checkf(Horace, TEXT("Horace is not valid"));
	
	HoraceController = Cast<AHA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	checkf(HoraceController, TEXT("HoraceController not valid"));

	Mesh->OnComponentHit.AddDynamic(this, &AHA_BlockBase::OnMeshHit);

	FOnTimelineFloat ShakeProgressUpdate;
	ShakeProgressUpdate.BindUFunction(this, "ShakeMovingUpdate");
	
	checkf(ShakeMovingCurve, TEXT("Shake moving curve not defined"));
	ShakeMovingTimeline.SetLooping(false);
	ShakeMovingTimeline.AddInterpFloat(ShakeMovingCurve, ShakeProgressUpdate);

	if (IsValid(ChildActorCollider))
	{
		ChildActorCollider->OnComponentBeginOverlap.AddDynamic(this, &AHA_BlockBase::OnCoinColliderBeginOverlap);
	}

	HideChildActor();
}

void AHA_BlockBase::OnMeshHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                              UPrimitiveComponent* PrimitiveComponent1, UE::Math::TVector<double> Vector, const FHitResult& HitResult)
{
	if (!UFunctionsLibrary::GetHorace(UGameplayStatics::GetPlayerCharacter(this, 0))) return;
	
	// Interact only if the player hit from to the bottom
	if (HitResult.ImpactNormal.Z != 1) return;
	
	HitBlock();
}

void AHA_BlockBase::OnCoinColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		Destroy();
	}
}

void AHA_BlockBase::PlaySoundEffect() const
{
	UFunctionsLibrary::PlayBlockSoundFx(this, InteractSound);
}

void AHA_BlockBase::PlayInactiveSoundEffect() const
{
	if (InteractSoundAfterInteract) UGameplayStatics::PlaySound2D(this, InteractSoundAfterInteract);
}

void AHA_BlockBase::ShowEffects() const
{
	UFunctionsLibrary::PlayBlockInteractFx(this, nullptr, InteractVFX_Particle, GetActorLocation());
}

void AHA_BlockBase::ShowPointsWidget(const FTransform& SpawnTransform)
{
	if (PointsActorClass)
	{
		FActorSpawnParameters SpawnParameters;		
		PointsActor = GetWorld()->SpawnActorDeferred<AHA_PointsActor>(PointsActorClass, FTransform::Identity);
		if (PointsActor)
		{
			PointsActor->SetPointsToAdd(Points);
		}

		UGameplayStatics::FinishSpawningActor(PointsActor, SpawnTransform);
	}
}

void AHA_BlockBase::AddPointsToPlayer()
{
	HoraceController->AddPoints(Points);
}

void AHA_BlockBase::SwapMaterial()
{
	if (InteractMaterial)
	{
		Mesh->SetMaterial(0, InteractMaterial);
	}
}

void AHA_BlockBase::SpawnCoinActor()
{
	if (CoinActorClass)
	{
		FActorSpawnParameters SpawnParameters;
		const FTransform SpawnTransform = GetActorTransform();
		
		CoinActor = GetWorld()->SpawnActorDeferred<AHA_Block_Coin>(CoinActorClass, FTransform::Identity);
		if (CoinActor)
		{
			// Nothing for now
		}

		UGameplayStatics::FinishSpawningActor(CoinActor, SpawnTransform);
	}
}

void AHA_BlockBase::HideMesh() const
{
	Mesh->SetVisibility(false);
}

void AHA_BlockBase::ShowMesh() const
{
	Mesh->SetVisibility(true);
}

void AHA_BlockBase::HideChildActor() const
{
	if (ChildActor) ChildActor->SetVisibility(false);
}

void AHA_BlockBase::ShowChildActor() const
{
	if (ChildActor) ChildActor->SetVisibility(true);
}

void AHA_BlockBase::ShakeTickTimeline()
{
	if (ShakeMovingTimeline.IsPlaying())
	{
		ShakeMovingTimeline.TickTimeline(ShakeTimeLineTickTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ShakeTimeLineTimerHandle);
	}
}

void AHA_BlockBase::ShakeMovingUpdate(float Alpha)
{
	const FVector Movement = FVector(0.f, 0.f, Alpha);
	Mesh->SetRelativeLocation(Movement);
}

void AHA_BlockBase::ShakeStartMoving()
{
	ShakeMovingTimeline.SetPlayRate(ShakeTimeLinePlayRate);
	ShakeMovingTimeline.PlayFromStart();
}

void AHA_BlockBase::ShakeBlock()
{
	ShakeStartMoving();
	GetWorldTimerManager().SetTimer(ShakeTimeLineTimerHandle, this, &AHA_BlockBase::ShakeTickTimeline, ShakeTimeLineTickTime, true, 0.0f);
}

void AHA_BlockBase::PBlockOn()
{
	HideMesh();
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShowChildActor();
	
}

void AHA_BlockBase::PBlockOff()
{
	ShowMesh();
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HideChildActor();
}


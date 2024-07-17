// NattySoft - All Right Reserved


#include "Characters/HA_Horace.h"

#include "Actors/Pipes/HA_WarpPipe.h"
#include "ActorsComponents/HA_FireBallComponent.h"
#include "ActorsComponents/HA_GrowingComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Core/HA_GameModeBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_Horace::AHA_Horace()
{
	FireBallSpawnPoint = CreateDefaultSubobject<UArrowComponent>("FireBallSpawnPoint");
	GrowingComponent = CreateDefaultSubobject<UHA_GrowingComponent>("GrowingComponent");
	FireBallComponent = CreateDefaultSubobject<UHA_FireBallComponent>("FireBallComponent");

	FireBallSpawnPoint->SetupAttachment(GetMesh());
}

void AHA_Horace::BeginPlay()
{
	Super::BeginPlay();
	SetNextSpawnLocation(GetActorTransform());

	FOnTimelineFloat DeathProgressUpdate;
	DeathProgressUpdate.BindUFunction(this, "DeathMovingUpdate");

	checkf(DeathMovingCurve, TEXT("Death moving curve not defined"));
	DeathMovingTimeline.SetLooping(false);
	DeathMovingTimeline.AddInterpFloat(DeathMovingCurve, DeathProgressUpdate);
}

AHA_PlayerController* AHA_Horace::GetHoraceController()
{
	if (HoraceController) return HoraceController;
	HoraceController = Cast<AHA_PlayerController>(GetController());
	return HoraceController;
}

void AHA_Horace::AdjustHitPoints(const int32 HitPointsModifier)
{

	// 1 - Set the new hit points
	HitPoints = FMath::Clamp(HitPointsModifier + HitPoints, 0, MaxHitPoints);
	if (HitPoints == EHP_Dead)
	{
		// Destroy actor
		PlayerDies();
		return;
	}
	
	// 2 - Change the material
	if (HitMaterials.Num() >= HitPoints && HitMaterials[HitPoints])
	{
		GetMesh()->SetMaterial(0, HitMaterials[HitPoints]);
	}

	// Level up
	if (HitPointsModifier > 0 && PowerUpSound)
	{
		UGameplayStatics::PlaySound2D(this, PowerUpSound);
	}

	// Getting hit
	if (HitPointsModifier < 0 && HitPoints != 0 && HitSound)
	{
		UGameplayStatics::PlaySound2D(this, HitSound);
		if (GrowingComponent)
		{
			GrowingComponent->Reverse();
		}
	}
}

void AHA_Horace::GotFlowerPower() const
{
	if (GrowingComponent)
	{
		GrowingComponent->Start();
	}
}

void AHA_Horace::ShootFireBall()
{
	if (!bHasFireFlower) return;
	if (!FireBallComponent) return;
	FTransform Transform = FireBallSpawnPoint->GetComponentTransform();
	FireBallComponent->ShootFireBall(Transform);
}

void AHA_Horace::InteractWithPipe()
{
	if (!OverlappingPipe) return;
	OverlappingPipe->Interact(this);
}

void AHA_Horace::SetNextSpawnLocation(const FTransform& InTransform) const
{
	AHA_GameModeBase* HoraceGameMode = Cast<AHA_GameModeBase>(UGameplayStatics::GetGameMode(this));
	checkf(HoraceGameMode, TEXT("Game mode has not been set to Horace Game Mode"));
	HoraceGameMode->SetSpawnTransform(InTransform);
}

void AHA_Horace::DestroyActorFX()
{
	DisableInput(GetHoraceController());
	UFunctionsLibrary::PlaySoundFx(this, DieSound);
	UFunctionsLibrary::PlayInteractFx(this, nullptr, DieEffect, GetActorLocation(), FVector(3.f));
	GetMovementComponent()->Deactivate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (DieAnimation) GetMesh()->PlayAnimation(DieAnimation, false);
}

void AHA_Horace::DestroyHorace()
{
	Destroy();
}

void AHA_Horace::PlayerDies()
{
	DestroyActorFX();
	PlayerStartsDeathSequence.Broadcast();
	StartDeathTransform = GetActorTransform();
	GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	DeathStartTimeline();
}

void AHA_Horace::DeathTickTimeline()
{
	if (DeathMovingTimeline.IsPlaying())
	{
		DeathMovingTimeline.TickTimeline(DeathTimeLineTickTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(DeathTimeLineTimerHandle);
		
		FTimerHandle DoOnceTimer;
		GetWorldTimerManager().SetTimer(DoOnceTimer, this, &AHA_Horace::DestroyHorace, 2.5f, true, 0.0f);
	}
}

void AHA_Horace::DeathMovingUpdate(float Alpha)
{
	FVector Location = StartDeathTransform.GetLocation();
	Location.Z += Alpha;
	GetMesh()->SetRelativeLocationAndRotation(Location, FRotator::ZeroRotator);
}

void AHA_Horace::DeathStartMoving()
{
	DeathMovingTimeline.SetPlayRate(DeathTimeLinePlayRate);
	DeathMovingTimeline.PlayFromStart();
}

void AHA_Horace::DeathStartTimeline()
{
	DeathStartMoving();
	GetWorldTimerManager().SetTimer(DeathTimeLineTimerHandle, this, &AHA_Horace::DeathTickTimeline, DeathTimeLineTickTime, true, 0.0f);
}
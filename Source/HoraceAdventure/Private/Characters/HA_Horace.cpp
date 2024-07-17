// NattySoft - All Right Reserved


#include "Characters/HA_Horace.h"

#include "Actors/Pipes/HA_WarpPipe.h"
#include "ActorsComponents/HA_FireBallComponent.h"
#include "ActorsComponents/HA_GrowingComponent.h"
#include "Components/ArrowComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Core/HA_GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AHA_Horace::AHA_Horace()
{
	FireBallSpawnPoint = CreateDefaultSubobject<UArrowComponent>("FireBallSpawnPoint");
	GrowingComponent = CreateDefaultSubobject<UHA_GrowingComponent>("GrowingComponent");
	FireBallComponent = CreateDefaultSubobject<UHA_FireBallComponent>("FireBallComponent");

	FireBallSpawnPoint->SetupAttachment(GetMesh());
	RespawnSize = FVector(.75f);
}

void AHA_Horace::BeginPlay()
{
	Super::BeginPlay();
	SetTransformAsNextSpawnLocation();
}

AHA_PlayerController* AHA_Horace::GetHoraceController()
{
	if (HoraceController) return HoraceController;
	HoraceController = Cast<AHA_PlayerController>(GetController());
	return HoraceController;
}

void AHA_Horace::SetTransformAsNextSpawnLocation()
{
	AHA_GameModeBase* HoraceGameMode = Cast<AHA_GameModeBase>(UGameplayStatics::GetGameMode(this));
	checkf(HoraceGameMode, TEXT("Game mode has not been set to Horace Game Mode"));
	HoraceGameMode->SetSpawnTransform(GetActorTransform());
}

void AHA_Horace::AdjustHitPoints(const int32 HitPointsModifier)
{

	// 1 - Set the new hit points
	HitPoints = FMath::Clamp(HitPointsModifier + HitPoints, 0, MaxHitPoints);
	if (HitPoints == EHP_Dead)
	{
		// Destroy actor
		Destroy();
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

void AHA_Horace::GotFlowerPower()
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

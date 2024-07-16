// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_FireFlower.h"

#include "Actors/Blocks/HA_Block_Fake_Breakable.h"
#include "Characters/HA_Horace.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"
#include "Particles/ParticleSystemComponent.h"

AHA_Block_FireFlower::AHA_Block_FireFlower()
{
	BoxFlower = CreateDefaultSubobject<UBoxComponent>("BoxFlower");
	MeshFlower = CreateDefaultSubobject<UStaticMeshComponent>("MeshFlower");
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	
	BoxFlower->SetupAttachment(Mesh);
	MeshFlower->SetupAttachment(BoxFlower);
	
	BoxFlower->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	BoxFlower->SetLineThickness(5.f);
	Arrow->SetRelativeLocation(FVector(0.f, 0.f, 150.f));

	MeshFlower->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AHA_Block_FireFlower::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat FlowerProgressUpdate;
	FlowerProgressUpdate.BindUFunction(this, "FlowerMovingUpdate");
	
	checkf(FlowerMovingCurve, TEXT("Flower moving curve not defined"));
	FlowerMovingTimeline.SetLooping(false);
	FlowerMovingTimeline.AddInterpFloat(FlowerMovingCurve, FlowerProgressUpdate);

	BoxFlower->OnComponentBeginOverlap.AddDynamic(this, &AHA_Block_FireFlower::OnBoxFlowerBeginOverlap);
}

void AHA_Block_FireFlower::HitBlock()
{
	Super::HitBlock();

	if (!bFinishedInteracting)
	{
		// This will make sure that the following logic will be run once
		bFinishedInteracting = true;

		// Play sounds
		PlaySoundEffect();
		
		// Show the effects
		ShowEffects();

		// Change the material
		SwapMaterial();
	
		// Shake the block
		ShakeBlock();

		// Glow effect for the block
		GlowBlock();

		// Move the flower up
		FlowerMove();
	}
}

void AHA_Block_FireFlower::GlowBlock()
{
	if (!GlowingVFX_Particle) return;
	PowerUpGlow = UGameplayStatics::SpawnEmitterAtLocation(this, GlowingVFX_Particle, MeshFlower->GetComponentLocation());
}

void AHA_Block_FireFlower::OnBoxFlowerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const AHA_Horace* CheckHorace = UFunctionsLibrary::GetHorace(OtherActor); !IsValid(CheckHorace)) return;
	
	// AHA_Horace* Horace = Cast<AHA_Horace>();
	// if (!Horace || Horace != OtherActor) return;

	// Spawn points widget
	FTransform SpawnTransform = GetActorTransform();
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z += 120.f;
	SpawnTransform.SetLocation(SpawnLocation);
	ShowPointsWidget(SpawnTransform);

	// Add points
	AddPointsToPlayer();

	// Destroy block components
	if (BoxFlower) BoxFlower->DestroyComponent();
	if (MeshFlower) MeshFlower->DestroyComponent();
	if (PowerUpGlow) PowerUpGlow->DestroyComponent();

	// Call got flower power
	Horace->GotFlowerPower();
}

void AHA_Block_FireFlower::FlowerTickTimeline()
{
	if (FlowerMovingTimeline.IsPlaying())
	{
		FlowerMovingTimeline.TickTimeline(FlowerTimeLineTickTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(FlowerTimeLineTimerHandle);
	}
}

void AHA_Block_FireFlower::FlowerMovingUpdate(float Alpha)
{
	if (!IsValid(BoxFlower)) return;

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("FlowerMovingUpdate: %f"), Alpha));
	const FVector Movement = FVector(0.f, 0.f, Alpha);
	BoxFlower->SetRelativeLocation(Movement);
}

void AHA_Block_FireFlower::FlowerStartMoving()
{
	FlowerMovingTimeline.SetPlayRate(FlowerTimeLinePlayRate);
	FlowerMovingTimeline.Play();
}

void AHA_Block_FireFlower::FlowerMove()
{
	FlowerStartMoving();
	GetWorldTimerManager().SetTimer(FlowerTimeLineTimerHandle, this, &AHA_Block_FireFlower::FlowerTickTimeline, FlowerTimeLineTickTime, true, 0.0f);
}

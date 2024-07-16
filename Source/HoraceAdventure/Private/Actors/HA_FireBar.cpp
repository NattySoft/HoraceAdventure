// NattySoft - All Right Reserved


#include "Actors/HA_FireBar.h"

#include "Characters/HA_Horace.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Libraries/FunctionsLibrary.h"

AHA_FireBar::AHA_FireBar()
{
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Ball = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Bar");
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");
	
	Box->SetupAttachment(GetRootComponent());
	Ball->SetupAttachment(GetRootComponent());
	
	Ball->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	RotatingMovement->RotationRate = FRotator(50.f, 0.f, 0.f);
	
}

void AHA_FireBar::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AHA_FireBar::OnBoxBeginOverlap);
}

void AHA_FireBar::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Ball->ClearInstances();
	for (int32 i = 0; i < FlameBallNumber; i++)
	{
		// Add instances of frame bar
		int32 NewDistance = FlameBallDistanceApart * i;
		FTransform InstanceTransform = FTransform();
		InstanceTransform.SetScale3D(FlameBallSize);
		InstanceTransform.SetLocation(FVector(0.f, 0.f, NewDistance));
		Ball->AddInstance(InstanceTransform);

		// Set the box collision
		const int32 NewBoxLocationZ = NewDistance / 2;
		Box->SetRelativeLocation(FVector(0.f, 0.f, NewBoxLocationZ));
		Box->SetBoxExtent(FVector(10.f, 50.f, NewBoxLocationZ));

		// Customize rate of rotation
		RotatingMovement->RotationRate = RotationRate;
	}
}

void AHA_FireBar::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bBoxHit) return;
	bBoxHit = true;
	
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	Horace->AdjustHitPoints(HitPointAdjustmentToPlayer);
	Horace->GetCharacterMovement()->Velocity = PlayerHitVelocity;

	FTimerHandle DelayHandle;
	GetWorldTimerManager().SetTimer(DelayHandle, this, &AHA_FireBar::ResetBoxHit, HitCooldown, true, 0.0f);
}

void AHA_FireBar::ResetBoxHit()
{
	// Reset the DoOnce
	bBoxHit = false;
}

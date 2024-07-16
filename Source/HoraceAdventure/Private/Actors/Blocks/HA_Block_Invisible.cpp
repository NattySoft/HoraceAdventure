// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_Invisible.h"

#include "Characters/HA_Horace.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_Block_Invisible::AHA_Block_Invisible()
{
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Mesh);
	Box->SetBoxExtent(FVector(100.f, 50.f, 100.f));
	Box->SetRelativeLocation(FVector(0.f, 0.f, 51.f));
	Mesh->SetCollisionResponseToChannel(ECC_FireBall, ECR_Ignore);
}

void AHA_Block_Invisible::BeginPlay()
{
	Super::BeginPlay();

	Horace = UFunctionsLibrary::GetHorace(UGameplayStatics::GetPlayerCharacter(this, 0));
	checkf(Horace, TEXT("Player character Horace not created"));
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AHA_Block_Invisible::OnBoxBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AHA_Block_Invisible::OnBoxEndOverlap);

	if (ChildActorCollider) ChildActorCollider->DestroyComponent();
	if (ChildActor) ChildActor->DestroyComponent();
	
	HideMesh();
}

void AHA_Block_Invisible::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Horace) return;

	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
}

void AHA_Block_Invisible::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != Horace) return;

	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	
}

void AHA_Block_Invisible::HitBlock()
{
	Super::HitBlock();

	if (!bFinishedInteracting)
	{
		// This will make sure that the following logic will be run once
		bFinishedInteracting = true;

		// Show the mesh and destroy the collider
		ShowMesh();
		Box->DestroyComponent();
		Mesh->SetCollisionResponseToChannel(ECC_FireBall, ECR_Block);

		// Play sounds
		PlaySoundEffect();
		
		// Show the effects
		ShowEffects();

		// Change the material
		SwapMaterial();
	
		// Spawn points widget
		ShowPointsWidget(GetActorTransform());

		// Spawn a coin actor
		SpawnCoinActor();
	
		// Add points to the player
		AddPointsToPlayer();

		// Shake the block
		ShakeBlock();
	}
	else
	{
		PlayInactiveSoundEffect();
		
	}
	
	
	// Destroy the actor
	// Destroy();
}

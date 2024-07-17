// NattySoft - All Right Reserved


#include "Actors/Blocks/HA_Block_P.h"

#include "Actors/Blocks/HA_Block_Base.h"
#include "Characters/HA_Horace.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

// Sets default values
AHA_Block_P::AHA_Block_P()
{
 	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxSmashed = CreateDefaultSubobject<UBoxComponent>("BoxSmashed");
	BlockBaseSmashed = CreateDefaultSubobject<UStaticMeshComponent>("BlockBaseSmashed");
	BlockTopSmashed = CreateDefaultSubobject<UStaticMeshComponent>("BlockTopSmashed");
	Music = CreateDefaultSubobject<UAudioComponent>("Music");

	SetRootComponent(DefaultSceneRoot);
	Plane->SetupAttachment(DefaultSceneRoot);
	Box->SetupAttachment(DefaultSceneRoot);
	BoxSmashed->SetupAttachment(DefaultSceneRoot);
	BlockBaseSmashed->SetupAttachment(DefaultSceneRoot);
	BlockTopSmashed->SetupAttachment(DefaultSceneRoot);
	
	Plane->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	Box->SetBoxExtent(FVector(42.f, 42.f, 50.f));
	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Box->SetCollisionResponseToAllChannels(ECR_Block);

	BoxSmashed->SetBoxExtent(FVector(42.f, 100.f, 13.f));
	BoxSmashed->SetCollisionObjectType(ECC_WorldStatic);
	BoxSmashed->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	BoxSmashed->SetCollisionResponseToAllChannels(ECR_Block);
	
	BlockBaseSmashed->SetVisibility(false);
	BlockTopSmashed->SetVisibility(false);

	Music->SetAutoActivate(false);
}

void AHA_Block_P::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentHit.AddDynamic(this, &AHA_Block_P::OnBoxComponentHit);
}

void AHA_Block_P::OnBoxComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!IsValid(Horace)) return;
	if (!FMath::IsNearlyEqual(Hit.ImpactNormal.Z, -1, 0.01f)) return; // Check for the down direction

	PlayEffects(Horace);
	PlayCameraShakeAndForceFeedback(Horace);
	ActivateHiddenBoxes();
	ActivateAllPBlocks();

	// Listen of the player died
	Horace->PlayerStartsDeathSequence.AddLambda([this]()
	{
		DeactivateAllPBlocksOnTimerOver();
	});
	
	FTimerHandle PBlockTimer;
	GetWorldTimerManager().SetTimer(PBlockTimer, this, &AHA_Block_P::DeactivateAllPBlocksOnTimerOver, BlockTimeDuration);
}

void AHA_Block_P::PlayEffects(AHA_Horace* Horace) const
{
	Horace->LaunchCharacter(FVector(0.f, 0.f, 400.f), false, false);
	if (CharacterLaunchSound) UGameplayStatics::PlaySound2D(this, CharacterLaunchSound);
	if (CharacterLaunchEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			CharacterLaunchEffect,
			BlockBaseSmashed->GetComponentLocation()
		);
	}
	Music->Play();
}

void AHA_Block_P::PlayCameraShakeAndForceFeedback(AHA_Horace* Horace) const
{
	if (CharacterLaunchShake) UGameplayStatics::PlayWorldCameraShake(this, CharacterLaunchShake, Horace->GetActorLocation(), 1000.f, 2000.f);
	if (CharacterForceFeedbackEffect) Horace->GetHoraceController()->ClientPlayForceFeedback(CharacterForceFeedbackEffect);
}

void AHA_Block_P::ActivateHiddenBoxes() const
{
	BlockBaseSmashed->SetVisibility(true);
	BlockTopSmashed->SetVisibility(true);
	Plane->DestroyComponent();
	Box->DestroyComponent();
}

void AHA_Block_P::ActivateAllPBlocks()
{
	UGameplayStatics::GetAllActorsWithTag(this, Tag, Blocks);
	for (AActor* Block : Blocks)
	{
		AHA_BlockBase* BlockBase = Cast<AHA_BlockBase>(Block);
		if (!IsValid(BlockBase)) continue;
		BlockBase->PBlockOn();
	}
}

void AHA_Block_P::DeactivateAllPBlocksOnTimerOver()
{
	for (AActor* Block : Blocks)
	{
		AHA_BlockBase* BlockBase = Cast<AHA_BlockBase>(Block);
		if (!IsValid(BlockBase)) continue;
		BlockBase->PBlockOff();
	}
	Music->Stop();
}
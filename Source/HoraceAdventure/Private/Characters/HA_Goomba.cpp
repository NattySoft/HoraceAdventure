// NattySoft - All Right Reserved


#include "Characters/HA_Goomba.h"
#include "PaperFlipbookComponent.h"
#include "Actors/HA_PointsActor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/HA_Horace.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

#include "Components/SphereComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"
#include "Weapons/HA_FireBall.h"

AHA_Goomba::AHA_Goomba()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetectRange = CreateDefaultSubobject<USphereComponent>("PlayerDetectRange");
	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("PaperFlipbook");
	StampBox = CreateDefaultSubobject<UBoxComponent>("StampBox");

	PlayerDetectRange->SetupAttachment(GetRootComponent());
	Collider->SetupAttachment(GetRootComponent());
	PaperFlipbook->SetupAttachment(Collider);
	StampBox->SetupAttachment(Collider);

	GetCapsuleComponent()->SetCapsuleHalfHeight(55.f);
	GetCapsuleComponent()->SetCapsuleRadius(50.f);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	PlayerDetectRange->SetSphereRadius(2000.f);
	Collider->SetSphereRadius(45.f);
	Collider->SetCollisionResponseToAllChannels(ECR_Block);
	Collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PaperFlipbook->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	StampBox->SetBoxExtent(FVector(40.f, 100.f, 3.f));
	StampBox->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	StampBox->SetLineThickness(3.f);
	StampBox->SetCollisionResponseToAllChannels(ECR_Block);
	StampBox->SetCollisionResponseToChannel(ECC_FireBall, ECR_Ignore);

	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	GetCharacterMovement()->MaxWalkSpeed = Speed;
	FlipbookPlayRateMultiplier = FMath::Clamp(Speed / 100.f, 0.1f, 3.f);

	GetCapsuleComponent()->SetCanEverAffectNavigation(false);
	Collider->SetCanEverAffectNavigation(false);
	StampBox->SetCanEverAffectNavigation(false);
	PlayerDetectRange->SetCanEverAffectNavigation(false);
	
}

void AHA_Goomba::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveDirectionWithPlayerInRange();
}

void AHA_Goomba::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AHA_Goomba::OnColliderBeginOverlap);
	Collider->OnComponentHit.AddDynamic(this, &AHA_Goomba::OnColliderHit);
	StampBox->OnComponentHit.AddDynamic(this, &AHA_Goomba::OnStampBoxHit);
	PlayerDetectRange->OnComponentBeginOverlap.AddDynamic(this, &AHA_Goomba::OnPlayerDetectRangeBegin);
	PlayerDetectRange->OnComponentEndOverlap.AddDynamic(this, &AHA_Goomba::OnPlayerDetectRangeEnd);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AHA_Goomba::OnCapsuleComponentHit);
}

void AHA_Goomba::OnCapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bCapsuleCheckActive) return;

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
	// 	FString::Printf(TEXT("Impact actor: %s"), *Hit.GetActor()->GetActorNameOrLabel()));
	
	bCapsuleCheckActive = false;
	FTimerHandle DoOnceHandle;
	constexpr float DoOnceTime = .5f;
	GetWorldTimerManager().SetTimer(DoOnceHandle, this, &AHA_Goomba::ResetCapsuleCheckActive, DoOnceTime);
	
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
	// 	FString::Printf(TEXT("Impact GetAbs: %f"), Hit.ImpactNormal.GetAbs().X));
	if (FMath::IsNearlyEqual(Hit.ImpactNormal.GetAbs().X, 1, 0.1f))
	{
		bMoveLeft = !bMoveLeft;
	}
}

void AHA_Goomba::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	Horace->AdjustHitPoints(Damage);
}

void AHA_Goomba::OnColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AHA_FireBall* FireBall = Cast<AHA_FireBall>(OtherActor);
	if (!FireBall) return;

	FireBall->Destroy();

	// Add points to the player
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!Horace) return;
	AddPointsToPlayer(Horace);

	// Destroy Goomba
	DestroyGoomba();
	
}

void AHA_Goomba::OnPlayerDetectRangeBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!UFunctionsLibrary::GetHorace(OtherActor)) return;
	bIsGateOpen = true;
}

void AHA_Goomba::OnPlayerDetectRangeEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!UFunctionsLibrary::GetHorace(OtherActor)) return;
	bIsGateOpen = false;
}

void AHA_Goomba::OnStampBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               FVector NormalImpulse, const FHitResult& Hit)
{
	if (!FMath::IsNearlyEqual(Hit.ImpactNormal.Z, -1, 0.1f)) return; // Check for the down direction

	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	SquishEffect();
	AddPointsToPlayer(Horace);

	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &AHA_Goomba::DestroyGoomba, 0.5f);
}

void AHA_Goomba::ResetCapsuleCheckActive()
 {
	bCapsuleCheckActive = true;
}

void AHA_Goomba::SquishEffect() const
{
	if (SquishSound) UGameplayStatics::PlaySound2D(this, SquishSound);
	Collider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	StampBox->DestroyComponent();
	PaperFlipbook->SetWorldScale3D(FVector(.25f, .25f, .1f));
	PaperFlipbook->AddWorldOffset(FVector(0.f, 0.f, -35.f));
	GetMovementComponent()->StopMovementImmediately();
}

void AHA_Goomba::AddPointsToPlayer(AHA_Horace* Horace) const
{
	const FTransform SpawnTransform = GetActorTransform();
	FActorSpawnParameters SpawnParameters;		
	AHA_PointsActor* PointsActor = GetWorld()->SpawnActorDeferred<AHA_PointsActor>(PointsActorClass, FTransform::Identity);
	if (PointsActor)
	{
		PointsActor->SetPointsToAdd(Points);
	}
	UGameplayStatics::FinishSpawningActor(PointsActor, SpawnTransform);
	Horace->GetHoraceController()->AddPoints(Points);
}

void AHA_Goomba::MoveDirectionWithPlayerInRange()
{
	if (bIsGateOpen)
	{
		if (bIsSeekerEnemy)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(
				GetController(),
				UGameplayStatics::GetPlayerCharacter(this, 0)
			);
		}
		else
		{
			FVector MoveInput = FVector::ZeroVector;
			if (bMoveLeft)
			{
				MoveInput.X = -1.f;
			}
			else
			{
				MoveInput.X = 1.f;
			}
			AddMovementInput(MoveInput);
			PaperFlipbook->SetPlayRate(FlipbookPlayRateMultiplier);
		}
	}
}

void AHA_Goomba::DestroyGoomba()
{
	UFunctionsLibrary::PlaySoundFx(this, ElimSound);
	UFunctionsLibrary::PlayInteractFx(this, nullptr, ElimEffect, Collider->GetComponentLocation());
	Destroy();
}

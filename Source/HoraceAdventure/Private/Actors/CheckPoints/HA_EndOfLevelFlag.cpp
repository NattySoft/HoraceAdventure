// NattySoft - All Right Reserved


#include "Actors/CheckPoints/HA_EndOfLevelFlag.h"

#include "Actors/HA_PointsActor.h"
#include "Characters/HA_Horace.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/FunctionsLibrary.h"

AHA_EndOfLevelFlag::AHA_EndOfLevelFlag()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerVolume");
	Flag = CreateDefaultSubobject<UStaticMeshComponent>("Flag");
	FlagPole = CreateDefaultSubobject<UStaticMeshComponent>("FlagPole");
	FlagBase = CreateDefaultSubobject<UStaticMeshComponent>("FlagBase");
	FlagTop = CreateDefaultSubobject<UStaticMeshComponent>("FlagTop");
	FlagEndPoint = CreateDefaultSubobject<UBillboardComponent>("FlagEndPoint");
	FireworksArea = CreateDefaultSubobject<UBoxComponent>("FireworksArea");
	PlayerEndPoint = CreateDefaultSubobject<UArrowComponent>("PlayerEndPoint");
	PlayerExplodePoint = CreateDefaultSubobject<UArrowComponent>("PlayerExplodePoint");
	PlayerStartPoint = CreateDefaultSubobject<UArrowComponent>("PlayerStartPoint");

	SetRootComponent(SceneComponent);
	TriggerVolume->SetupAttachment(SceneComponent);
	Flag->SetupAttachment(SceneComponent);
	FlagPole->SetupAttachment(SceneComponent);
	FlagBase->SetupAttachment(SceneComponent);
	FlagTop->SetupAttachment(SceneComponent);
	FlagEndPoint->SetupAttachment(SceneComponent);
	FireworksArea->SetupAttachment(SceneComponent);
	PlayerEndPoint->SetupAttachment(SceneComponent);
	PlayerExplodePoint->SetupAttachment(SceneComponent);
	PlayerStartPoint->SetupAttachment(SceneComponent);

	Flag->SetRelativeLocation(FVector(85.f, 0.f, 845.f));
	Flag->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	Flag->SetRelativeScale3D(FVector(1.5f, 1.f, 1.f));
	
	FlagPole->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	FlagPole->SetRelativeScale3D(FVector(.2f, .2f, 8.f));
	FlagPole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FlagBase->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	
	FlagTop->SetRelativeLocation(FVector(0.f, 0.f, 895.f));
	FlagTop->SetRelativeScale3D(FVector(.5f));
	FlagTop->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FlagEndPoint->SetRelativeLocation(FVector(85.f, 0.f, 150.f));
	FlagEndPoint->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	FireworksArea->SetRelativeLocation(FVector(850.f, 0.f, 700.f));
	FireworksArea->SetBoxExtent(FVector(500.f, 200.f, 300.f));
	FireworksArea->SetLineThickness(5.f);
	FireworksArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PlayerEndPoint->SetRelativeLocation(FVector(-25.f, 30.f, 190.f));
	PlayerExplodePoint->SetRelativeLocation(FVector(850.f, 0.f, 500.f));
	PlayerStartPoint->SetRelativeLocation(FVector(-25.f, 30.f, 845.f));

	TriggerVolume->SetRelativeLocation(FVector(30.f, 0.f, 1000.f));
	TriggerVolume->SetBoxExtent(FVector(32.f, 200.f, 1000.f));
	TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void AHA_EndOfLevelFlag::BeginPlay()
{
	Super::BeginPlay();

	HoraceController = Cast<AHA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	checkf(HoraceController, TEXT("%hs HoraceController missing"), __FUNCTION__);

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AHA_EndOfLevelFlag::OnTriggerVolumeBeginOverlap);
	
}

void AHA_EndOfLevelFlag::SetFlagStartLocation()
{
	// Set the starting point for the flag
	const FVector FlagAttachLocation = Horace->GetFlagAttachPoint()->GetComponentLocation();
	const FVector FlagLocation = Flag->GetComponentLocation();
	if (FlagAttachLocation.Z > FlagLocation.Z)
	{
		FlagStartPoint = FlagLocation;
		// Reset the player if he jumps over the flag pole
		Horace->GetCapsuleComponent()->SetWorldLocation(PlayerStartPoint->GetComponentLocation());
	}
	else
	{
		FlagStartPoint = FVector(FlagLocation.X, FlagLocation.Y, FlagAttachLocation.Z);
	}
	Flag->SetWorldLocation(FlagStartPoint);
}

void AHA_EndOfLevelFlag::SetPlayerPositionAndPlayAnim() const
{
	// Face the character to the flag pole
	Horace->GetCapsuleComponent()->SetWorldRotation(PlayerEndPoint->GetComponentRotation());
	Horace->GetCapsuleComponent()->AddLocalOffset(FVector(0.f, 30.f, 0.f));

	// Set Character Position and play anim
	Horace->GetCharacterMovement()->GravityScale = 0.f;
	Horace->GetCharacterMovement()->Deactivate();
	if (PlayerGrabPoleAnimation)
	{
		Horace->GetMesh()->PlayAnimation(PlayerGrabPoleAnimation, false);
		Horace->GetMesh()->SetPosition(1.9f, true);
	}
}

void AHA_EndOfLevelFlag::AnimateCharacterDownThePole()
{
	const FVector ToLocation = PlayerEndPoint->GetComponentLocation();
	float MoveTime = 1.f;
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = Horace;
	UKismetSystemLibrary::MoveComponentTo(
		Horace->GetCapsuleComponent(),
		ToLocation,
		PlayerEndPoint->GetComponentRotation(),
		false, false, MoveTime, false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	if (PlayerJumpOffPoleAnimation)
	{
		DELAY(MoveTime, [this]()
		{
			Horace->GetMesh()->PlayAnimation(PlayerJumpOffPoleAnimation, false);	
		});
	}

	if (PlayerJumpFallLoopAnimation)
	{
		DELAY(MoveTime, [this, LatentInfo]()
		{
			Horace->GetMesh()->PlayAnimation(PlayerJumpFallLoopAnimation, false);
			UKismetSystemLibrary::MoveComponentTo(
				Horace->GetCapsuleComponent(),
				PlayerExplodePoint->GetComponentLocation(),
				PlayerExplodePoint->GetComponentRotation(),
				false, false, .5, false,
				EMoveComponentAction::Move,
				LatentInfo
			);
		});
	}

	DELAY(2.f, [this]()
	{
		UFunctionsLibrary::PlayInteractFx(
			this, nullptr,
			ExplodeEffect,
			Horace->GetCapsuleComponent()->GetComponentLocation(),
			FVector(2.f)
		);
		UFunctionsLibrary::PlaySoundFx(this, ExplosionSound);

		Horace->GetCapsuleComponent()->SetVisibility(false, true);
		PlayAllFireworks();
	});
}

void AHA_EndOfLevelFlag::AnimateFlagDownThePole()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = Flag;
	const FVector ToLocation = FlagEndPoint->GetRelativeLocation();
	UKismetSystemLibrary::MoveComponentTo(
		Flag,
		ToLocation,
		FlagEndPoint->GetRelativeRotation(),
		false, false, 1.f, false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void AHA_EndOfLevelFlag::PlayAllFireworks()
{
	if (!HoraceController) return;

	const FString LevelTime = FString::FromInt(HoraceController->GetLevelTime());
	const FString RightLevelTime = LevelTime.Right(1);
	const FString FireworkShowSpecialNumberString = FString::FromInt(FireworkShowSpecialNumber);

	// Check if the last digit of time remaining = "Fireworks Show #"
	if (FireworkShowSpecialNumberString.Equals(RightLevelTime))
	{
		float TimerTime = 0.f;
		for (int i = 0; i < FireworkShowSpecialNumber; i++)
		{
			constexpr float BaseTimerTime = .5f;
			FTimerHandle FireworkTimer;
			TimerTime = i == 0 ? BaseTimerTime : TimerTime + BaseTimerTime;
			GetWorldTimerManager().SetTimer(FireworkTimer, this, &AHA_EndOfLevelFlag::PlaySingleFirework, TimerTime);
		}
	}
}

void AHA_EndOfLevelFlag::PlaySingleFirework()
{
	const FVector FireworksLocation = UKismetMathLibrary::RandomPointInBoundingBox(
					FireworksArea->GetComponentLocation(),
					FireworksArea->GetUnscaledBoxExtent()
				);

	FireworkLocale = FireworksLocation;
	UFunctionsLibrary::PlayInteractFx(this, nullptr,
		FireworksEffect, FireworkLocale,
		FVector(10.f));

	UFunctionsLibrary::PlaySoundFx(this, FireworksSound, FireworkLocale);

	FTransform PointsTransform;
	PointsTransform.SetLocation(FireworkLocale);
	ShowPointsWidget(PointsTransform, FireworkPoints);
}

void AHA_EndOfLevelFlag::ShowPointsWidget(const FTransform& SpawnTransform, const int32 Points) const
{
	if (PointsActorClass)
	{
		FActorSpawnParameters SpawnParameters;		
		AHA_PointsActor* PointsActor = GetWorld()->SpawnActorDeferred<AHA_PointsActor>(PointsActorClass, FTransform::Identity);
		if (PointsActor) PointsActor->SetPointsToAdd(Points);
		if (HoraceController) HoraceController->AddPoints(Points);
		UGameplayStatics::FinishSpawningActor(PointsActor, SpawnTransform);
	}
}

void AHA_EndOfLevelFlag::StartAnimationsAndEffects()
{
	UFunctionsLibrary::PlaySoundFx(GetWorld(), FlagPoleSound);
	AnimateCharacterDownThePole();
	AnimateFlagDownThePole();
}

void AHA_EndOfLevelFlag::OnTriggerVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bTriggerVolumeBeginOverlapped) return;
	Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!IsValid(Horace)) return;

	bTriggerVolumeBeginOverlapped = true;
	HoraceController->DisableInput(HoraceController);

	// Dispatch the event for the level completed
	LevelCompleteDelegate.Broadcast();

	SetFlagStartLocation();
	SetPlayerPositionAndPlayAnim();

	FTimerHandle FxHandler;
	GetWorldTimerManager().SetTimer(FxHandler, this, &AHA_EndOfLevelFlag::StartAnimationsAndEffects, 1.f);
}

// NattySoft - All Right Reserved


#include "Actors/HA_Platform_Actor.h"

#include "Characters/HA_Horace.h"
#include "Components/BoxComponent.h"
#include "Libraries/FunctionsLibrary.h"

AHA_Platform_Actor::AHA_Platform_Actor()
{
	AutoReceiveInput = EAutoReceiveInput::Type::Player0;
	
	CollisionTop = CreateDefaultSubobject<UBoxComponent>("CollisionTop");
	CollisionTop->SetupAttachment(Mesh);

	CollisionBottom = CreateDefaultSubobject<UBoxComponent>("CollisionBottom");
	CollisionBottom->SetupAttachment(Mesh);

	CollisionTop->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionTop->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	CollisionBottom->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBottom->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh->SetRelativeScale3D(FVector(2.f, 5.f, .2f));
	CollisionTop->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CollisionTop->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	CollisionBottom->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	CollisionBottom->SetBoxExtent(FVector(50.f, 50.f, 50.f));
}

void AHA_Platform_Actor::BeginPlay()
{
	Super::BeginPlay();

	CollisionTop->OnComponentBeginOverlap.AddDynamic(this, &AHA_Platform_Actor::OnCollisionTopStartOverlap);
	CollisionTop->OnComponentEndOverlap.AddDynamic(this, &AHA_Platform_Actor::OnCollisionTopEndOverlap);
	
	CollisionBottom->OnComponentBeginOverlap.AddDynamic(this, &AHA_Platform_Actor::OnCollisionBottomStartOverlap);
	CollisionBottom->OnComponentEndOverlap.AddDynamic(this, &AHA_Platform_Actor::OnCollisionBottomEndOverlap);
}


void AHA_Platform_Actor::OnCollisionTopStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		bIsOnTopOfPlatform = true;
	}
}

void AHA_Platform_Actor::OnCollisionTopEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor)) return;
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		bIsOnTopOfPlatform = false;
	}
}

void AHA_Platform_Actor::OnCollisionBottomStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}

void AHA_Platform_Actor::OnCollisionBottomEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor)) return;
	if (UFunctionsLibrary::GetHorace(OtherActor))
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}
}

void AHA_Platform_Actor::DropPlayerFromPlatform()
{
	if (!bIsOnTopOfPlatform) return;
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}


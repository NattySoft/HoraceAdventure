// NattySoft - All Right Reserved


#include "Actors/Hazards/HA_InstantDeath.h"

#include "Characters/HA_Horace.h"
#include "Components/BoxComponent.h"
#include "Libraries/FunctionsLibrary.h"

AHA_InstantDeath::AHA_InstantDeath()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("Death Volume");
	Box->SetupAttachment(GetRootComponent());

	Box->SetBoxExtent(FVector(400.f, 400.f, 50.f));
	Box->SetLineThickness(3.f);
}

void AHA_InstantDeath::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AHA_InstantDeath::OnBoxBeginOverlap);
}

void AHA_InstantDeath::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	Horace->PlayerDies();
}


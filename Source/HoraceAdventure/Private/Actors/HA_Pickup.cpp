// NattySoft - All Right Reserved


#include "Actors/HA_Pickup.h"

#include "Characters/HA_Horace.h"
#include "Components/SphereComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_Pickup::AHA_Pickup()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetSphereRadius(30.f);

	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AHA_Pickup::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AHA_Pickup::OnSphereBeginOverlap);
}

void AHA_Pickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(OtherActor);
	if (!Horace) return;

	if (PickupSound) UGameplayStatics::PlaySound2D(this, PickupSound);
	if (PickupEffect) UGameplayStatics::SpawnEmitterAtLocation(this, PickupEffect, GetActorLocation());

	if (Horace->GetHoraceController())
	{
		Horace->GetHoraceController()->AddCoin(CoinsValue);	
	}
	
	Destroy();
}

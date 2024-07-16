// NattySoft - All Right Reserved


#include "Actors/Pipes/HA_WarpPipe.h"

#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

AHA_WarpPipe::AHA_WarpPipe()
{
	PipeBody = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Pipe Body");
	PipeBody->SetupAttachment(GetRootComponent());

	PipeInside = CreateDefaultSubobject<UStaticMeshComponent>("Pipe Inside");
	PipeInside->SetupAttachment(Mesh);

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Collision->SetupAttachment(Mesh);

	WarpInPoint = CreateDefaultSubobject<UBillboardComponent>("Warp In Point");
	WarpInPoint->SetupAttachment(GetRootComponent());

	WarpOutPoint = CreateDefaultSubobject<UBillboardComponent>("Warp Out Point");
	WarpOutPoint->SetupAttachment(GetRootComponent());

	PipeBody->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	PipeBody->SetRelativeScale3D(FVector(2.25f, 2.25f, .1f));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 35.f));
	Mesh->SetRelativeScale3D(FVector(2.75f, 2.75f, .5f));

	PipeInside->SetRelativeLocation(FVector(0.f, 0.f, 25.5f));
	PipeInside->SetRelativeScale3D(FVector(.8f, .8f, .5f));

	Collision->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	Collision->SetCapsuleHalfHeight(300.f);
	Collision->SetCapsuleRadius(40.f);

	Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WarpInPoint->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	WarpOutPoint->SetRelativeLocation(FVector(0.f, 0.f, -35.f));
	
}

// NattySoft - All Right Reserved


#include "Actors/Levels/HA_Clouds.h"

#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

AHA_Clouds::AHA_Clouds()
{
	Mesh->DestroyComponent();
	
	SpawnArea = CreateDefaultSubobject<UBoxComponent>("Spawn Area");
	Clouds = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Clouds");
	
	SpawnArea->SetupAttachment(GetRootComponent());
	Clouds->SetupAttachment(GetRootComponent());
	
	SpawnArea->SetBoxExtent(FVector());
	SpawnArea->SetLineThickness(20.f);

	Clouds->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	Clouds->SetCastShadow(false);
	
}

void AHA_Clouds::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpawnArea->SetBoxExtent(FVector(SpawnExtendX, SpawnExtendY, SpawnExtendZ));

	if (!Clouds) return;
	
	Clouds->ClearInstances();
	for (int i = 0; i < InstancesToSpawn; i++)
	{
		FTransform InstanceTransform;

		const FVector InstanceLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetRelativeLocation(), SpawnArea->GetUnscaledBoxExtent());
		const float ScaleInstance = FMath::FRandRange(ScaleMin, ScaleMax);
		
		InstanceTransform.SetLocation(InstanceLocation);
		InstanceTransform.SetScale3D(FVector(ScaleInstance));
		

		Clouds->AddInstance(InstanceTransform);
	}
	
}

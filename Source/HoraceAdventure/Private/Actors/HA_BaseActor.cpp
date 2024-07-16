// NattySoft - All Right Reserved


#include "Actors/HA_BaseActor.h"

// Sets default values
AHA_BaseActor::AHA_BaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneComponent);
	
}

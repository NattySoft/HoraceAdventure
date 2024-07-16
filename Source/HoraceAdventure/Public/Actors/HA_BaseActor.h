// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_BaseActor.generated.h"

class AHA_Horace;
class UBoxComponent;

UCLASS()
class HORACEADVENTURE_API AHA_BaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHA_BaseActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
};

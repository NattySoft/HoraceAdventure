// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "HA_Clouds.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Clouds : public AHA_BaseActor
{
	GENERATED_BODY()

public:
	AHA_Clouds();
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditDefaultsOnly)
	UInstancedStaticMeshComponent* Clouds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clouds")
	int32 InstancesToSpawn = 25;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clouds")
	float SpawnExtendX = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clouds")
	float SpawnExtendY = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clouds")
	float SpawnExtendZ = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clouds")
	float ScaleMin = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clouds")
	float ScaleMax = 10.f;
	
};

// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_CheckPointBase.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class HORACEADVENTURE_API AHA_CheckPointBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHA_CheckPointBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UArrowComponent* RespawnTransform;
	
	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UStaticMeshComponent* FlagPivotPoint;

	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UStaticMeshComponent* FlagBase;
	
	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UStaticMeshComponent* Flag;

	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UStaticMeshComponent* FlagArm;

	
};

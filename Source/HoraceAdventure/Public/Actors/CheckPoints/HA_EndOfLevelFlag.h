// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_EndOfLevelFlag.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class HORACEADVENTURE_API AHA_EndOfLevelFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	AHA_EndOfLevelFlag();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UBoxComponent* TriggerVolume;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UStaticMeshComponent* Flag;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UStaticMeshComponent* FlagPole;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UStaticMeshComponent* FlagBase;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UStaticMeshComponent* FlagTop;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UBillboardComponent* FlagEndPoint;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UBoxComponent* FireworksArea;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UArrowComponent* PlayerEndPoint;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UArrowComponent* PlayerExplodePoint;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UArrowComponent* PlayerStartPoint;

};

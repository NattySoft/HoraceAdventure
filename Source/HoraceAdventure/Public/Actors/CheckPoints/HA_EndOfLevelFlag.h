// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_EndOfLevelFlag.generated.h"

class AHA_PlayerController;
class AHA_Horace;
class UArrowComponent;
class UBoxComponent;

DECLARE_MULTICAST_DELEGATE(FLevelCompleteDelegate)

UCLASS()
class HORACEADVENTURE_API AHA_EndOfLevelFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	AHA_EndOfLevelFlag();

protected:
	// ############## FUNCTIONS ###############
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnTriggerVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									 const FHitResult& SweepResult);


	
	// ############## PROPERTIES ###############

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

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UAnimationAsset* PlayerGrabPoleAnimation;
	

	UPROPERTY()
	AHA_Horace* Horace;

	UPROPERTY()
	AHA_PlayerController* HoraceController;
	
	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	FVector FlagStartPoint;
	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	FVector FireworkLocale;
	UPROPERTY(EditAnywhere, Category="EndOfLevelFlag")
	int32 FireworkPoints = 500;
	UPROPERTY(EditAnywhere, Category="EndOfLevelFlag")
	int32 FireworkShowSpecialNumber = 7;
	
private:
	bool bTriggerVolumeBeginOverlapped = false;
	
public:
	FLevelCompleteDelegate LevelCompleteDelegate;

	void SetFlagStartLocation();
	void SetPlayerPositionAndPlayAnim() const;
	
};

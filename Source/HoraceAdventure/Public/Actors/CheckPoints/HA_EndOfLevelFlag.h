// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "HA_EndOfLevelFlag.generated.h"

class AHA_PointsActor;
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

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UAnimationAsset* PlayerJumpOffPoleAnimation;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UAnimationAsset* PlayerJumpFallLoopAnimation;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UParticleSystem* ExplodeEffect;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	UParticleSystem* FireworksEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	USoundBase* FlagPoleSound;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	USoundBase* FireworksSound;

	UPROPERTY(EditDefaultsOnly, Category="EndOfLevelFlag")
	TSubclassOf<AHA_PointsActor> PointsActorClass;
	
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


	// ######### Pole timeline ##########
	UPROPERTY(EditAnywhere, Category="EndOfLevelFlag")
	UCurveFloat* PoleMovingCurve = nullptr;

	float PoleTimeLineTickTime = 0.01f;
	float PoleTimeLinePlayRate = 1.f;
	
	FTimeline PoleMovingTimeline;
	FTimerHandle PoleTimeLineTimerHandle;
	
	UFUNCTION()
	void PoleTickTimeline();
	
	UFUNCTION()
	void PoleMovingUpdate(float Alpha) const;
	void PoleStartMoving();
	void PoleStartTimeline();
	// ######### END Pole timeline ##########
	
private:
	bool bTriggerVolumeBeginOverlapped = false;
	
public:
	FLevelCompleteDelegate LevelCompleteDelegate;

	void SetFlagStartLocation();
	void SetPlayerPositionAndPlayAnim() const;

	UFUNCTION()
	void StartAnimationsAndEffects();
	
	void AnimateCharacterDownThePole();
	void AnimateFlagDownThePole();
	void PlayAllFireworks();

	UFUNCTION()
	void PlaySingleFirework();
	void ShowPointsWidget(const FTransform& SpawnTransform, int32 Points) const;
};

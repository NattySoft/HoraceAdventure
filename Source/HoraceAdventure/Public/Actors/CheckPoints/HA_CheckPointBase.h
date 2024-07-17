// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "HA_CheckPointBase.generated.h"

class UNiagaraSystem;
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

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



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

	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	USoundBase* CheckPointSound;

	UPROPERTY(EditDefaultsOnly, Category="CheckPoint")
	UNiagaraSystem* CheckPointEffect;

	bool bFlagArmRotated = false;
	FRotator FlagArmRotateStart = FRotator(0.f, 0.f, -90.f);
	FRotator FlagArmRotateEnd = FRotator(0.f, 0.f, 0.f);
	
	// ######### CheckPoint timeline ##########
	UPROPERTY(EditAnywhere, Category="CheckPoint")
	UCurveFloat* CheckPointMovingCurve = nullptr;

	UPROPERTY(EditAnywhere, Category="CheckPoint")
	float CheckPointTimeLineTickTime = 0.01f;

	UPROPERTY(EditAnywhere, Category="CheckPoint")
	float CheckPointTimeLinePlayRate = 1.f;
	
	FTimeline CheckPointMovingTimeline;
	FTimerHandle CheckPointTimeLineTimerHandle;
	
	UFUNCTION()
	void CheckPointTickTimeline();
	
	UFUNCTION()
	void CheckPointMovingUpdate(float Alpha) const;
	void CheckPointStartMoving();
	void CheckPointMove();
	// ######### END CheckPoint timeline ##########
	
};

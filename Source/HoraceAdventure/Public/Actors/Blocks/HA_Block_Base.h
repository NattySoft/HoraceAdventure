// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "Components/TimelineComponent.h"
#include "Interfaces/PlatformerInterface.h"
#include "HA_Block_Base.generated.h"

class USphereComponent;
class AHA_Block_Coin;
class AHA_PointsActor;
class AHA_PlayerController;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_BlockBase : public AHA_BaseActor, public IPlatformerInterface
{
	GENERATED_BODY()

public:
	AHA_BlockBase();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult);

	UFUNCTION()
	void OnCoinColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									const FHitResult& SweepResult);
	
	void ShowEffects() const;
	void PlaySoundEffect() const;
	void PlayInactiveSoundEffect() const;
	void ShowPointsWidget(const FTransform& SpawnTransform);
	void AddPointsToPlayer();
	void SwapMaterial();
	void SpawnCoinActor();
	void HideMesh() const;
	void ShowMesh() const;
	void HideChildActor() const;
	void ShowChildActor() const;

	UPROPERTY()
	AHA_Horace* Horace;
	
	UPROPERTY()
	AHA_PlayerController* HoraceController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* ChildActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* ChildActorCollider;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFinishedInteracting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoinsToAdd = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Points = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* InteractVFX_Niagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* InteractVFX_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* InteractSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* InteractSoundAfterInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* InteractMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PointsActorClass;

	UPROPERTY()
	AHA_PointsActor* PointsActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CoinActorClass;

	UPROPERTY()
	AHA_Block_Coin* CoinActor;

protected:
	// ########### SHAKE TIMELINE ############
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	UCurveFloat* ShakeMovingCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float ShakeTimeLineTickTime = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeline")
	float ShakeTimeLinePlayRate = 1.f;
	
	FTimeline ShakeMovingTimeline;
	FTimerHandle ShakeTimeLineTimerHandle;
	
	UFUNCTION()
	void ShakeTickTimeline();
	
	UFUNCTION()
	void ShakeMovingUpdate(float Alpha);
	void ShakeStartMoving();

	
public:
	void ShakeBlock();

	void PBlockOn();
	void PBlockOff();
};

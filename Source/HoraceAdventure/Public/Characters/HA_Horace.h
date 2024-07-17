// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/HA_BaseCharacter.h"
#include "Components/TimelineComponent.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "HA_Horace.generated.h"

class AHA_WarpPipe;
class UHA_FireBallComponent;
class UHA_GrowingComponent;
class AHA_PlayerController;

DECLARE_MULTICAST_DELEGATE(FPlayerStartsDeathSequence);

UCLASS()
class HORACEADVENTURE_API AHA_Horace : public AHA_BaseCharacter
{
	GENERATED_BODY()

public:
	AHA_Horace();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AHA_PlayerController* HoraceController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Horace|Components")
	UArrowComponent* FireBallSpawnPoint;
	
	UPROPERTY(EditAnywhere, Category="Horace|Components")
	UHA_GrowingComponent* GrowingComponent;

	UPROPERTY(EditAnywhere, Category="Horace|Components")
	UHA_FireBallComponent* FireBallComponent;

	
	
	UPROPERTY(EditAnywhere, Category="Horace|Apparence")
	TArray<UMaterialInstance*> HitMaterials;

	UPROPERTY(EditAnywhere, Category="Horace|Apparence")
	FVector RespawnSize = FVector(.75f);


	
	UPROPERTY(EditAnywhere, Category="Horace|Sounds")
	USoundBase* PowerUpSound;

	UPROPERTY(EditAnywhere, Category="Horace|Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Horace|Sounds")
	USoundBase* DieSound;

	UPROPERTY(EditAnywhere, Category="Horace|Effects")
	UParticleSystem* DieEffect;

	UPROPERTY(EditAnywhere, Category="Horace|Effects")
	UAnimationAsset* DieAnimation;
	
	UPROPERTY(EditAnywhere, Category="Horace|Stats")
	int32 HitPoints = EHP_Small;

	UPROPERTY(EditAnywhere, Category="Horace|Stats")
	int32 MaxHitPoints = 2;

	UPROPERTY(EditAnywhere, Category="Horace|Health")
	FVector PlayerScaleSmall = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, Category="Horace|Health")
	bool bHasFireFlower = false;

	UPROPERTY()
	AHA_WarpPipe* OverlappingPipe;

	FTransform StartDeathTransform;
	// ######### Death timeline ##########
	UPROPERTY(EditAnywhere, Category="Horace|Death Timelines")
	UCurveFloat* DeathMovingCurve = nullptr;

	float DeathTimeLineTickTime = 0.01f;
	float DeathTimeLinePlayRate = 1.f;
	
	FTimeline DeathMovingTimeline;
	FTimerHandle DeathTimeLineTimerHandle;
	
	UFUNCTION()
	void DeathTickTimeline();
	
	UFUNCTION()
	void DeathMovingUpdate(float Alpha);
	void DeathStartMoving();
	void DeathStartTimeline();
	// ######### END Death timeline ##########
	
private:
	void DestroyActorFX();

	UFUNCTION()
	void DestroyHorace();
	
public:
	// Broadcast the death sequence to listeners
	FPlayerStartsDeathSequence PlayerStartsDeathSequence;
	
	FORCEINLINE int32 GetHitPoints() const { return HitPoints; }
	FORCEINLINE bool HasFireFlower() const { return bHasFireFlower; }
	FORCEINLINE void SetHasFireFlower(const bool InValue) { bHasFireFlower = InValue; }
	FORCEINLINE FVector GetPlayerScaleSmall() const { return PlayerScaleSmall; }
	FORCEINLINE void SetOverlappingPipe(AHA_WarpPipe* Pipe) { OverlappingPipe = Pipe; }
	FORCEINLINE FVector GetRespawnSize() const { return RespawnSize; }
	
	AHA_PlayerController* GetHoraceController();
	void AdjustHitPoints(const int32 HitPointsModifier);
	void GotFlowerPower() const;
	
	UFUNCTION(BlueprintCallable)
	void ShootFireBall();
	
	UFUNCTION(BlueprintCallable)
	void InteractWithPipe();

	void SetNextSpawnLocation(const FTransform& InTransform) const;

	UFUNCTION(CallInEditor)
	void PlayerDies();
};

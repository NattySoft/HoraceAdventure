// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "HA_FireBall.generated.h"

DECLARE_MULTICAST_DELEGATE(FFireballDestroyedDelegate);

class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_FireBall : public AActor
{
	GENERATED_BODY()

public:
	AHA_FireBall();

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnFireBallBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float InitialSpeed = 2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float MaxSpeed = 2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	bool bShouldBounce = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float Bounciness = .5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float Friction = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float DestroyAfterSeconds = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	int32 BounceMaxCounter = 2;
	int32 BounceCounter = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	UParticleSystem* ExplodeEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	USoundBase* ExplodeSound;

private:
	void Explode();
	
public:
	int32 FireBallIndex = 0;
	FFireballDestroyedDelegate FireballDestroyedDelegate;
};

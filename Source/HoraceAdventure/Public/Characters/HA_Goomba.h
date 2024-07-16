// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HA_Goomba.generated.h"

class AHA_Horace;
class AHA_PointsActor;
class AHA_PlayerController;
class UBoxComponent;
class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class HORACEADVENTURE_API AHA_Goomba : public ACharacter
{
	GENERATED_BODY()

public:
	AHA_Goomba();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnCapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnStampBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnPlayerDetectRangeBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								  const FHitResult& SweepResult);
	UFUNCTION()
	void OnPlayerDetectRangeEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* PlayerDetectRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* PaperFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* StampBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Goomba")
	int32 Damage = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Goomba")
	int32 Points = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SquishSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AHA_PointsActor> PointsActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ElimSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ElimEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Goomba")
	float Speed = 200.f;

	UPROPERTY(VisibleAnywhere, Category="Goomba")
	float FlipbookPlayRateMultiplier = 0.f;

	UPROPERTY(EditAnywhere, Category="Goomba")
	bool bMoveLeft = true;

	bool bIsGateOpen = false;
	bool bCapsuleCheckActive = true;
	void ResetCapsuleCheckActive();

	UPROPERTY(EditAnywhere, Category="Goomba")
	bool bIsSeekerEnemy = false;
	
private:
	void SquishEffect() const;
	void AddPointsToPlayer(AHA_Horace* Horace) const;
	void MoveDirectionWithPlayerInRange();
	
	UFUNCTION()
	void DestroyGoomba();
};

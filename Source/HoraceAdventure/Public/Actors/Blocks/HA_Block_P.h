// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "HA_Block_P.generated.h"

class AHA_Horace;
class UBoxComponent;
class UCameraShakeBase;
class UForceFeedbackEffect;

UCLASS()
class HORACEADVENTURE_API AHA_Block_P : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHA_Block_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Plane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BlockBaseSmashed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BlockTopSmashed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxSmashed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Music;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Tag = PBlockTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Blocks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlockTimeDuration = 8.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CharacterLaunchSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* CharacterLaunchEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> CharacterLaunchShake;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UForceFeedbackEffect* CharacterForceFeedbackEffect;
	
private:
	void PlayEffects(AHA_Horace* Horace) const;
	void PlayCameraShakeAndForceFeedback(AHA_Horace* Horace) const;
	void ActivateHiddenBoxes() const;
	void ActivateAllPBlocks();
	UFUNCTION()
	void DeactivateAllPBlocksOnTimerOver();
};

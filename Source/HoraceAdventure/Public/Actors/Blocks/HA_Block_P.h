// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "HA_Block_P.generated.h"

class AHA_LevelSettings;
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
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Plane;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BlockBaseSmashed;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BlockTopSmashed;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxSmashed;

	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* Music;

	UPROPERTY(EditDefaultsOnly)
	FName Tag = PBlockTag;

	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> Blocks;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* CharacterLaunchSound;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* CharacterLaunchEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> CharacterLaunchShake;
	
	UPROPERTY(EditDefaultsOnly)
	UForceFeedbackEffect* CharacterForceFeedbackEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HA Block P")
	float BlockTimeDuration = 8.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HA Block P")
	AHA_LevelSettings* LevelSettings;
	
private:
	void PlayEffects(AHA_Horace* Horace) const;
	void PlayCameraShakeAndForceFeedback(AHA_Horace* Horace) const;
	void ActivateHiddenBoxes() const;
	void ActivateAllPBlocks();
	UFUNCTION()
	void DeactivateAllPBlocksOnTimerOver();
};

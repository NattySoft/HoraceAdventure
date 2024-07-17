// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "Components/TimelineComponent.h"
#include "HA_WarpPipe.generated.h"

class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_WarpPipe : public AHA_BaseActor
{
	GENERATED_BODY()

public:
	AHA_WarpPipe();
	void Interact(AHA_Horace* InHorace);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void MovePlayerUp();
	void MovePlayerDown();
	
	UPROPERTY(EditDefaultsOnly)
	UInstancedStaticMeshComponent* PipeBody;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PipeInside;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
	UBillboardComponent* WarpInPoint;
	
	UPROPERTY(EditDefaultsOnly)
	UBillboardComponent* WarpOutPoint;

	UPROPERTY(EditDefaultsOnly, Category="WarpPipe")
	USoundBase* WarpSound;
	
	UPROPERTY(EditAnywhere, Category="WarpPipe", meta=(MakeEditWidget="true"))
	FVector PipeEndPoint = FVector(0.f, 0.f, -100.f);

	UPROPERTY(EditAnywhere, Category="WarpPipe")
	bool bCanInteract = false;

	UPROPERTY(EditAnywhere, Category="WarpPipe")
	bool bIsDownPipe = true;

	bool bIsGateOpen = false;

	UPROPERTY(EditAnywhere, Category="WarpPipe")
	bool bIsExitingRaisingUp = true;
	bool bIsExiting = false;

private:
	UPROPERTY(VisibleAnywhere, Category="WarpPipe")
	AHA_Horace* HoraceRef;

	UPROPERTY(EditAnywhere, Category="WarpPipe")
	FVector WarpToLocale = FVector::ZeroVector;
	
	// ######### Pipe timeline ##########
	UPROPERTY(EditAnywhere, Category="WarpPipe")
	UCurveFloat* PipeMovingCurve = nullptr;

	UPROPERTY(EditAnywhere, Category="WarpPipe")
	float PipeTimeLineTickTime = 0.01f;

	UPROPERTY(EditAnywhere, Category="WarpPipe")
	float PipeTimeLinePlayRate = 1.f;
	
	FTimeline PipeMovingTimeline;
	FTimerHandle PipeTimeLineTimerHandle;
	
	UFUNCTION()
	void PipeTickTimeline();
	
	UFUNCTION()
	void PipeMovingUpdate(float Alpha) const;
	void PipeStartMoving();
	void PipeMove();
	// ######### END Pipe timeline ##########

	UFUNCTION()
	void PlayWarpSound() const;

	UFUNCTION()
	void PlayExit();
};

// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
#include "HA_Platform_Actor.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Platform_Actor : public AHA_BaseActor
{
	GENERATED_BODY()

public:
	AHA_Platform_Actor();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionTop;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBottom;
	
private:
	bool bIsOnTopOfPlatform = false;
	
	UFUNCTION()
	void OnCollisionTopEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnCollisionTopStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionBottomEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnCollisionBottomStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintCallable)
	void DropPlayerFromPlatform();
};

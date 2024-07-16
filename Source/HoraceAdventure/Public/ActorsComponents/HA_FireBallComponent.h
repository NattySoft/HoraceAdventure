// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HA_FireBallComponent.generated.h"


class AHA_FireBall;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORACEADVENTURE_API UHA_FireBallComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHA_FireBallComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Weapons")
	TSubclassOf<AHA_FireBall> FireBallClass;

	UPROPERTY(EditAnywhere, Category="Weapons")
	USoundBase* FireBallSound;

	UPROPERTY(EditAnywhere, Category="Weapons")
	int32 MaxFireBalls = 5;

private:
	int32 FireBallsLastIndex = 0;
	TMap<int32, TObjectPtr<AHA_FireBall>> LiveFireBalls;
	
public:	
	UFUNCTION(BlueprintCallable)
	void ShootFireBall(FTransform& Transform);
};

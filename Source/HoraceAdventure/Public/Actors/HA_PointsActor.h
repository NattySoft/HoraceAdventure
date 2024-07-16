// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "HA_PointsActor.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_PointsActor : public AActor
{
	GENERATED_BODY()

public:
	AHA_PointsActor();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PointsToAdd = 0;

public:
	FORCEINLINE void SetPointsToAdd(const int32 InValue) { PointsToAdd = InValue; }
	FORCEINLINE int32 GetPointsToAdd() const { return PointsToAdd; }
};

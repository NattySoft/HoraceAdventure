// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Actors/HA_BaseActor.h"
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
	
protected:
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
};

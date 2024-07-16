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
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	
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

	UPROPERTY(EditAnywhere, Category="WarpPipe", meta=(MakeEditWidget="true"))
	FVector PipeEndPoint = FVector(0.f, 0.f, -100.f);

	
};

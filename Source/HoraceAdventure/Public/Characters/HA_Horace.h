// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/HA_BaseCharacter.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "HA_Horace.generated.h"

class AHA_WarpPipe;
class UHA_FireBallComponent;
class UHA_GrowingComponent;
class AHA_PlayerController;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_Horace : public AHA_BaseCharacter
{
	GENERATED_BODY()

public:
	AHA_Horace();
	
protected:
	UPROPERTY()
	AHA_PlayerController* HoraceController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player Components")
	UArrowComponent* FireBallSpawnPoint;
	
	UPROPERTY(EditAnywhere, Category="Player Components")
	UHA_GrowingComponent* GrowingComponent;

	UPROPERTY(EditAnywhere, Category="Player Components")
	UHA_FireBallComponent* FireBallComponent;
	
	UPROPERTY(EditAnywhere, Category="Player Apparence")
	TArray<UMaterialInstance*> HitMaterials;

	UPROPERTY(EditAnywhere, Category="Player Sounds")
	USoundBase* PowerUpSound;

	UPROPERTY(EditAnywhere, Category="Player Sounds")
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category="Player Stats")
	int32 HitPoints = EHP_Small;

	UPROPERTY(EditAnywhere, Category="Player Stats")
	int32 MaxHitPoints = 2;

	UPROPERTY(EditAnywhere, Category="Player Health")
	FVector PlayerScaleSmall = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, Category="Player Health")
	bool bHasFireFlower = false;

	UPROPERTY()
	AHA_WarpPipe* OverlappingPipe;
	
public:
	FORCEINLINE int32 GetHitPoints() const { return HitPoints; }
	FORCEINLINE bool HasFireFlower() const { return bHasFireFlower; }
	FORCEINLINE void SetHasFireFlower(const bool InValue) { bHasFireFlower = InValue; }
	FORCEINLINE FVector GetPlayerScaleSmall() const { return PlayerScaleSmall; }
	FORCEINLINE void SetOverlappingPipe(AHA_WarpPipe* Pipe) { OverlappingPipe = Pipe; }
	
	AHA_PlayerController* GetHoraceController();
	void AdjustHitPoints(const int32 HitPointsModifier);
	void GotFlowerPower();

	UFUNCTION(BlueprintCallable)
	void ShootFireBall();
	
	UFUNCTION(BlueprintCallable)
	void InteractWithPipe();
};

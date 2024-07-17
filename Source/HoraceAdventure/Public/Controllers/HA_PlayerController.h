// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HA_PlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCoinChangesDelegate, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLivesChangesDelegate, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointsChangesDelegate, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeChangesDelegate, int32)

class AHA_HUD;

UCLASS()
class HORACEADVENTURE_API AHA_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY()
	AHA_HUD* HoraceHud;
	
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 Coins = 0;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 CoinsThreshold = 100;
	
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 Lives = 3;
	int32 MaxLives = 100;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 Points = 0;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 LevelTime = 500;
	
	UPROPERTY(EditAnywhere, Category="Gameplay")
	USoundBase* LivesUpSound;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	USoundBase* PointsSound;
	
public:
	// Delegates
	FOnCoinChangesDelegate OnCoinChangesDelegate;
	FOnLivesChangesDelegate OnLivesChangesDelegate;
	FOnPointsChangesDelegate OnPointsChangesDelegate;
	FOnTimeChangesDelegate OnTimeChangesDelegate;
	// End Delegates
	
	UFUNCTION(BlueprintCallable)
	AHA_HUD* GetHoraceHUD();

	FORCEINLINE int32 GetLives() const { return Lives; }
	
	void AddCoin(const int32 InValue);
	void AddLife(const int32 InValue);
	void AddPoints(const int32 InPoints);
};

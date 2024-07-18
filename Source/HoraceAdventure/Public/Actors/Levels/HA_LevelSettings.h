// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_LevelSettings.generated.h"

class AHA_PlayerController;
class AHA_GameModeBase;

UCLASS()
class HORACEADVENTURE_API AHA_LevelSettings : public AActor
{
	GENERATED_BODY()
	
public:	
	AHA_LevelSettings();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category="LevelSettings|Sounds")
	UAudioComponent* LevelMusicComponent;

	UPROPERTY(EditAnywhere, Category="LevelSettings|Sounds")
	UAudioComponent* TimeRunningOutWarningComponent;

	UPROPERTY(EditAnywhere, Category="LevelSettings|Sounds")
	UAudioComponent* TimeExpiredComponent;

	UPROPERTY(EditAnywhere, Category="LevelSettings|Sounds")
	UAudioComponent* LevelCompleteComponent;

	UPROPERTY(EditAnywhere, Category="LevelSettings|Settings")
	int32 TimeLimitCurrent = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	int32 TimeLimitMax = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	int32 TimeRunningOutWarning = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	float TimePlayRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	USoundBase* CurrentLevelMusic;

private:
	UPROPERTY()
	AHA_GameModeBase* GameMode;

	UPROPERTY()
	AHA_PlayerController* PlayerController;

	FTimerHandle LevelTimer;
	
	void PlayerRespawned();
	void ResetLevelTime();
	void SetAudioToPlay() const;

	UFUNCTION()
	void StartLevelTimer();
	void RunLevelTimer();
};

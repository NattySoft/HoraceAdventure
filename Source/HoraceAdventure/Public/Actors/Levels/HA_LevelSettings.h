// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA_LevelSettings.generated.h"

class AHA_EndOfLevelFlag;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	USoundBase* LevelCompleteSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	AHA_EndOfLevelFlag* EndOfLevelFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	int32 LevelTimeAwardPoints = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LevelSettings|Settings")
	FName LevelToGoTo;
	
private:
	UPROPERTY()
	AHA_GameModeBase* GameMode;

	UPROPERTY()
	AHA_PlayerController* PlayerController;

	FTimerHandle LevelTimer;

	void StartGameLoop();
	
	void PlayerRespawned();
	void ResetLevelTime();
	void SetAudioToPlay() const;

	UFUNCTION()
	void StartLevelTimer();
	void RunLevelTimer();

	UFUNCTION()
	void RestartMusic();
	void StopAnyMusicAndTimer();

	void CheckEndOfLevelCompleted();

	UFUNCTION()
	void StartDecrementLevelTime();
	UFUNCTION()
	void DecrementLevelTimeUpdate();

	UFUNCTION()
	void MoveToNextLevel();
	
public:
	FORCEINLINE UAudioComponent* GetLevelMusicComponent() const { return LevelMusicComponent; }
};

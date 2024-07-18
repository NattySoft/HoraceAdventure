// NattySoft - All Right Reserved


#include "Actors/Levels/HA_LevelSettings.h"

#include "Actors/CheckPoints/HA_EndOfLevelFlag.h"
#include "Characters/HA_Horace.h"
#include "Components/AudioComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Core/HA_GameModeBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

AHA_LevelSettings::AHA_LevelSettings()
{
	PrimaryActorTick.bCanEverTick = false;

	LevelMusicComponent = CreateDefaultSubobject<UAudioComponent>("LevelMusic");
	TimeRunningOutWarningComponent = CreateDefaultSubobject<UAudioComponent>("TimeRunningOutWarning");
	TimeExpiredComponent = CreateDefaultSubobject<UAudioComponent>("TimeExpired");
	LevelCompleteComponent = CreateDefaultSubobject<UAudioComponent>("LevelComplete");

	LevelMusicComponent->SetAutoActivate(false);
	TimeRunningOutWarningComponent->SetAutoActivate(false);
	TimeExpiredComponent->SetAutoActivate(false);
	LevelCompleteComponent->SetAutoActivate(false);
}

void AHA_LevelSettings::BeginPlay()
{
	checkf(EndOfLevelFlag, TEXT("AHA_LevelSettings::BeginPlay EndOfLevelFlag has not been selected in the level"));
	
	Super::BeginPlay();

	GameMode = Cast<AHA_GameModeBase>(UGameplayStatics::GetGameMode(this));
	checkf(GameMode, TEXT("AHA_LevelSettings::BeginPlay Game is not a type of AHA_GameModeBase"));

	PlayerController = Cast<AHA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	checkf(GameMode, TEXT("AHA_LevelSettings::BeginPlay PlayerController is not a type of AHA_PlayerController"));
	
	ResetLevelTime();
	StartGameLoop();
}

void AHA_LevelSettings::StartGameLoop()
{
	PlayerRespawned();
	SetAudioToPlay();
	StartLevelTimer();
	StopAnyMusicAndTimer();
	CheckEndOfLevelCompleted();
}

void AHA_LevelSettings::PlayerRespawned()
{
	GameMode->PlayerRespawned.AddLambda([this]()
	{
		LevelMusicComponent->SetPitchMultiplier(1.0f);
		StartGameLoop();
	});
}

void AHA_LevelSettings::ResetLevelTime()
{
	PlayerController->SetLevelTime(TimeLimitMax);
	TimeLimitCurrent = TimeLimitMax;
}

void AHA_LevelSettings::SetAudioToPlay() const
{
	if (!CurrentLevelMusic) return;
	LevelMusicComponent->SetSound(CurrentLevelMusic);
	DELAY(0.75, [this]()
	{
		LevelMusicComponent->Play();
	});
}

void AHA_LevelSettings::StartLevelTimer()
{
	GetWorldTimerManager().SetTimer(LevelTimer, this, &AHA_LevelSettings::RunLevelTimer, TimePlayRate, true);
}

void AHA_LevelSettings::RunLevelTimer()
{
	if (TimeLimitCurrent == 0)
	{
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, LevelTimer);
		LevelMusicComponent->Stop();
		TimeRunningOutWarningComponent->Stop();
		AHA_Horace* Horace = UFunctionsLibrary::GetHorace(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (Horace) Horace->PlayerDies();
		return;
	}
	
	TimeLimitCurrent--;
	PlayerController->SetLevelTime(TimeLimitCurrent);

	if (TimeLimitCurrent == TimeRunningOutWarning)
	{
		LevelMusicComponent->SetPaused(true);
		TimeRunningOutWarningComponent->Play();
		TimeRunningOutWarningComponent->OnAudioFinished.AddDynamic(this, &AHA_LevelSettings::RestartMusic);
	}

	// 2.8 is the time that TimeRunningOutWarningComponent takes to play
	// FTimerHandle RestartHandler;
	// GetWorldTimerManager().SetTimer(RestartHandler, this, &AHA_LevelSettings::RestartMusic, 3.8f, false);
}

void AHA_LevelSettings::RestartMusic()
{
	LevelMusicComponent->SetPaused(false);
	LevelMusicComponent->SetPitchMultiplier(1.05f);
}

void AHA_LevelSettings::StopAnyMusicAndTimer()
{
	AHA_Horace* Horace = UFunctionsLibrary::GetHorace(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Horace)
	{
		Horace->PlayerStartsDeathSequence.AddLambda([this]()
		{
			LevelMusicComponent->Stop();
			TimeRunningOutWarningComponent->Stop();
			UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, LevelTimer);
		});
	}
}

void AHA_LevelSettings::CheckEndOfLevelCompleted()
{
	EndOfLevelFlag->LevelCompleteDelegate.AddLambda([this]()
	{
		LevelMusicComponent->Stop();
		TimeRunningOutWarningComponent->Stop();
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, LevelTimer);
		
		FTimerHandle StartDecrementLevelTimer;
		GetWorldTimerManager().SetTimer(StartDecrementLevelTimer, this, &AHA_LevelSettings::StartDecrementLevelTime, 1.f);
	});
}

void AHA_LevelSettings::StartDecrementLevelTime()
{
	LevelCompleteComponent->Activate();
	
	const int32 LoopCount = PlayerController->GetLevelTime();
	float TimerTime = 0.f;
	for (int i = 0; i < LoopCount; i++)
	{
		constexpr float BaseTimerTime = .05f;
		FTimerHandle DecrementLevelTimer;
		TimerTime = i == 0 ? BaseTimerTime : TimerTime + BaseTimerTime;
		GetWorldTimerManager().SetTimer(DecrementLevelTimer, this, &AHA_LevelSettings::DecrementLevelTimeUpdate, TimerTime);
	}
}

void AHA_LevelSettings::DecrementLevelTimeUpdate()
{
	PlayerController->SetLevelTime(PlayerController->GetLevelTime() - 1);
	PlayerController->AddPoints(LevelTimeAwardPoints);
	UFunctionsLibrary::PlaySoundFx(this, LevelCompleteSound);
}

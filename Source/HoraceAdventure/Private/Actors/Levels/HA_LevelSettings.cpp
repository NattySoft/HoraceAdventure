// NattySoft - All Right Reserved


#include "Actors/Levels/HA_LevelSettings.h"

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
	Super::BeginPlay();

	GameMode = Cast<AHA_GameModeBase>(UGameplayStatics::GetGameMode(this));
	checkf(GameMode, TEXT("AHA_LevelSettings::BeginPlay Game is not a type of AHA_GameModeBase"));

	PlayerController = Cast<AHA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	checkf(GameMode, TEXT("AHA_LevelSettings::BeginPlay PlayerController is not a type of AHA_PlayerController"));
	
	PlayerRespawned();
	ResetLevelTime();
	SetAudioToPlay();
}

void AHA_LevelSettings::PlayerRespawned()
{
	GameMode->PlayerRespawned.AddLambda([this]()
	{
		LevelMusicComponent->SetPitchMultiplier(1.0f);
		PlayerRespawned();
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
		LevelTimer.Invalidate();
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
	}
}

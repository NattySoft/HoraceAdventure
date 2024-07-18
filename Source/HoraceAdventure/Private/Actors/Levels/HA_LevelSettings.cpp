// NattySoft - All Right Reserved


#include "Actors/Levels/HA_LevelSettings.h"

#include "Components/AudioComponent.h"
#include "Controllers/HA_PlayerController.h"
#include "Core/HA_GameModeBase.h"
#include "Kismet/GameplayStatics.h"

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

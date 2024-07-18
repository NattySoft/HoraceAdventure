// NattySoft - All Right Reserved


#include "Actors/Levels/HA_LevelSettings.h"

#include "Components/AudioComponent.h"

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

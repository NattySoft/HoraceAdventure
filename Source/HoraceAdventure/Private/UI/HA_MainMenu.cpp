// NattySoft - All Right Reserved


#include "UI/HA_MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"

void UHA_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonPlay->OnClicked.AddDynamic(this, &UHA_MainMenu::OnButtonPlayClicked);
	ButtonPlay->OnHovered.AddDynamic(this, &UHA_MainMenu::OnButtonPlayHovered);
	ButtonPlay->OnUnhovered.AddDynamic(this, &UHA_MainMenu::OnButtonPlayUnhovered);

	FTimerHandle IntroTimer;
	GetWorld()->GetTimerManager().SetTimer(IntroTimer, this, &UHA_MainMenu::PlayIntroAnimation, 2.f, false);
}

void UHA_MainMenu::OnButtonPlayClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level_001");
}

void UHA_MainMenu::OnButtonPlayHovered()
{
	PlayAnimation(ScalePlayButton);
}

void UHA_MainMenu::OnButtonPlayUnhovered()
{
	PlayAnimation(ScalePlayButton, 0.f, 1.f, EUMGSequencePlayMode::Reverse);
}

void UHA_MainMenu::PlayIntroAnimation()
{
	PlayAnimation(Intro);
	UFunctionsLibrary::PlaySoundFx(GetWorld(), IntroSound);
}

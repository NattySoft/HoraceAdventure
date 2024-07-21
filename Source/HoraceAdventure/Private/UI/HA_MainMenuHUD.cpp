// NattySoft - All Right Reserved


#include "UI/HA_MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"
#include "UI/HA_MainMenu.h"

void AHA_MainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void AHA_MainMenuHUD::ShowMenu()
{
	if (MainMenuWidgetClass)
	{
		const UWorld* World = GetWorld();
		check(World);
		
		APlayerController* InController = UGameplayStatics::GetPlayerController(World, 0);
		check(InController);
		
		MainMenuWidget = CreateWidget<UHA_MainMenu>(InController, MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();

		InController->SetShowMouseCursor(true);
		UFunctionsLibrary::PlaySoundFx(World, MenuSound);
	}
}

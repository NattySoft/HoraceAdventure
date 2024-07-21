// NattySoft - All Right Reserved


#include "UI/HA_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Controllers/HA_PlayerController.h"
#include "Libraries/FunctionsLibrary.h"
#include "UI/HA_Overlay.h"
#include "UI/HA_PauseMenu.h"

void AHA_HUD::BeginPlay()
{
	Super::BeginPlay();
}

void AHA_HUD::AddCharacterOverlay(APlayerController* InController)
{
	if (!OverlayWidget)
	{
		if (AHA_PlayerController* HoraceController = Cast<AHA_PlayerController>(InController); HoraceController && OverlayWidgetClass)
		{
			OverlayWidget = CreateWidget<UHA_Overlay>(InController, OverlayWidgetClass);
			OverlayWidget->SetPlayerController(HoraceController);
		}
	}
	
	if (OverlayWidget) OverlayWidget->AddToViewport();
}

void AHA_HUD::ShowPauseMenu(APlayerController* InController)
{
	if (!InController) return;

	InController->SetPause(true);
	if (!PauseMenuWidget)
	{
		if (AHA_PlayerController* HoraceController = Cast<AHA_PlayerController>(InController); HoraceController && PauseMenuWidgetClass)
		{
			PauseMenuWidget = CreateWidget<UHA_PauseMenu>(InController, PauseMenuWidgetClass);
			PauseMenuWidget->SetPlayerController(HoraceController);
		}
	}
	
	if (PauseMenuWidget)
	{
		PauseMenuWidget->AddToViewport();
		UFunctionsLibrary::PlaySoundFx(GetWorld(), PauseMenuWidget->PauseSound);
	}
}

void AHA_HUD::HidePauseMenu() const
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->OnButtonContinueClicked();
	}
}

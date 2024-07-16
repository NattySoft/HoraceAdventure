// NattySoft - All Right Reserved


#include "UI/HA_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Controllers/HA_PlayerController.h"
#include "UI/HA_Overlay.h"

void AHA_HUD::BeginPlay()
{
	Super::BeginPlay();
}

void AHA_HUD::AddCharacterOverlay(APlayerController* InController)
{
	if (AHA_PlayerController* HoraceController = Cast<AHA_PlayerController>(InController); HoraceController && OverlayWidgetClass)
	{
		OverlayWidget = CreateWidget<UHA_Overlay>(InController, OverlayWidgetClass);
		OverlayWidget->SetPlayerController(HoraceController);
		OverlayWidget->AddToViewport();
	}
}

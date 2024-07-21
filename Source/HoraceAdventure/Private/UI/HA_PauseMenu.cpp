// NattySoft - All Right Reserved


#include "UI/HA_PauseMenu.h"

#include "Components/Button.h"
#include "Controllers/HA_PlayerController.h"
#include "Libraries/FunctionsLibrary.h"

void UHA_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonContinue->OnClicked.AddDynamic(this, &UHA_PauseMenu::OnButtonContinueClicked);
}

void UHA_PauseMenu::OnButtonContinueClicked()
{
	if (HoraceController)
	{
		HoraceController->SetPause(false);
		HoraceController->SetShowMouseCursor(false);

		const FInputModeGameOnly GameOnly;
		HoraceController->SetInputMode(GameOnly);
	}
	RemoveFromParent();
	UFunctionsLibrary::PlaySoundFx(this, PauseSound);
}

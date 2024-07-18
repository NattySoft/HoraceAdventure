// NattySoft - All Right Reserved


#include "UI/HA_Overlay.h"

#include "Components/TextBlock.h"
#include "Controllers/HA_PlayerController.h"

void UHA_Overlay::NativeConstruct()
{
	Super::NativeConstruct();
	BindControllerDelegates();
}

void UHA_Overlay::BindControllerDelegates()
{
	if (!HoraceController) return;

	HoraceController->OnCoinChangesDelegate.AddLambda([this](const int32 InValue)
	{
		CoinValue_Text->SetText(FText::FromString(FString::Printf(TEXT("%d"), InValue)));
	});

	HoraceController->OnLivesChangesDelegate.AddLambda([this](const int32 InValue)
	{
		CharacterLives_Text->SetText(FText::FromString(FString::Printf(TEXT("%d"), InValue)));
	});

	HoraceController->OnPointsChangesDelegate.AddLambda([this](const int32 InValue)
	{
		PointsValue_Text->SetText(FText::FromString(FString::Printf(TEXT("%d"), InValue)));
	});

	HoraceController->OnTimeChangesDelegate.AddLambda([this](const int32 InValue)
	{
		TimerValue_Text->SetText(FText::FromString(FString::Printf(TEXT("%d"), InValue)));
	});
}

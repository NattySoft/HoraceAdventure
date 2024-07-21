// NattySoft - All Right Reserved


#include "Controllers/HA_PlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Libraries/FunctionsLibrary.h"
#include "UI/HA_HUD.h"

void AHA_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (GetHoraceHUD())
	{
		GetHoraceHUD()->AddCharacterOverlay(this);
		OnCoinChangesDelegate.Broadcast(Coins);
		OnLivesChangesDelegate.Broadcast(Lives);
		OnPointsChangesDelegate.Broadcast(Points);
		OnTimeChangesDelegate.Broadcast(LevelTime);
	}
}

AHA_HUD* AHA_PlayerController::GetHoraceHUD()
{
	HoraceHud = HoraceHud == nullptr ? Cast<AHA_HUD>(GetHUD()) : HoraceHud;
	return HoraceHud;
}

void AHA_PlayerController::TogglePauseMenu()
{
	if (!bShowMouseCursor)
	{
		bShowMouseCursor = true;
		GetHoraceHUD()->ShowPauseMenu(this);
	}
	else
	{
		bShowMouseCursor = false;
		GetHoraceHUD()->HidePauseMenu();
	}
}

void AHA_PlayerController::AddCoin(const int32 InValue)
{
	if (Coins + InValue >= CoinsThreshold)
	{
		Coins = Coins + InValue - CoinsThreshold;
		AddLife(1);
	}
	else
	{
		Coins = FMath::Clamp(Coins + InValue, 0, CoinsThreshold);
	}

	OnCoinChangesDelegate.Broadcast(Coins);
}

void AHA_PlayerController::AddLife(const int32 InValue)
{
	Lives += InValue;
	Lives = FMath::Clamp(Lives, 0, MaxLives);
	OnLivesChangesDelegate.Broadcast(Lives);
	
	if (LivesUpSound && InValue > 0)
	{
		UGameplayStatics::PlaySound2D(this, LivesUpSound);
	}
	
	if (Lives == 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "LV_MainMenu");
	}
}

void AHA_PlayerController::AddPoints(const int32 InPoints)
{
	Points += InPoints;
	if (PointsSound)
	{
		UGameplayStatics::PlaySound2D(this, PointsSound);
	}
	OnPointsChangesDelegate.Broadcast(Points);
}

void AHA_PlayerController::SetLevelTime(const int32 InValue)
{
	LevelTime = InValue;
	OnTimeChangesDelegate.Broadcast(LevelTime);
}

void AHA_PlayerController::SetLives(const int32 Value)
{
	Lives = Value;
	OnLivesChangesDelegate.Broadcast(Lives);
}

void AHA_PlayerController::SetCoins(const int32 Value)
{
	Coins = Value;
	OnCoinChangesDelegate.Broadcast(Coins);
}

void AHA_PlayerController::SetPoints(const int32 Value)
{
	Points = Value;
	OnPointsChangesDelegate.Broadcast(Points);
}

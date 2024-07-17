// NattySoft - All Right Reserved


#include "Controllers/HA_PlayerController.h"

#include "Kismet/GameplayStatics.h"
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
		// OnTimeChangesDelegate.Broadcast(Time);
	}
}

AHA_HUD* AHA_PlayerController::GetHoraceHUD()
{
	HoraceHud = HoraceHud == nullptr ? Cast<AHA_HUD>(GetHUD()) : HoraceHud;
	return HoraceHud;
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

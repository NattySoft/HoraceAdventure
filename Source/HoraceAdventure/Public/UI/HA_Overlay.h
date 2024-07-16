// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HA_Overlay.generated.h"

class AHA_PlayerController;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API UHA_Overlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY()
	AHA_PlayerController* HoraceController;
	
public:
	void SetPlayerController(AHA_PlayerController* InController) { HoraceController = InController; }
	
	UPROPERTY(meta=(BindWidget))
	UImage* Character_Image;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CharacterX_Text;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CharacterLives_Text;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Coin_Image;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CoinX_Text;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CoinValue_Text;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PointsValue_Text;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Timer_Image;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TimerValue_Text;

private:
	void BindControllerDelegates();
};

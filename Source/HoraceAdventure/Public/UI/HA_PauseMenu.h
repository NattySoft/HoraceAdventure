// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HA_PauseMenu.generated.h"

class AHA_PlayerController;
class UButton;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API UHA_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	AHA_PlayerController* HoraceController;

	UPROPERTY(meta=(BindWidget))
	UButton* ButtonContinue;

public:
	void SetPlayerController(AHA_PlayerController* InController) { HoraceController = InController; }
	
	UFUNCTION()
	void OnButtonContinueClicked();

	UPROPERTY(EditAnywhere, Category="Gameplay")
	USoundBase* PauseSound;
	
};

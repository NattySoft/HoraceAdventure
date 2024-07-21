// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HA_MainMenuHUD.generated.h"

class UHA_MainMenu;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_MainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	USoundBase* MenuSound;
	
private:
	UPROPERTY()
	UHA_MainMenu* MainMenuWidget;
	
public:
	void ShowMenu();
	
};
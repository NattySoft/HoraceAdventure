// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HA_MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API UHA_MainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonPlayClicked();

	UFUNCTION()
	void OnButtonPlayHovered();
	
	UFUNCTION()
	void OnButtonPlayUnhovered();
	
public:
	UPROPERTY(EditAnywhere)
	USoundBase* IntroSound;
	
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonPlay;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* Intro;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* ScalePlayButton;
	
private:
	UFUNCTION()
	void PlayIntroAnimation();
};

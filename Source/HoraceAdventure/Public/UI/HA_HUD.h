// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HA_HUD.generated.h"

class AHA_Horace;
class UHA_Overlay;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_HUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AHA_Horace* OwningPlayer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY()
	UHA_Overlay* OverlayWidget;

public:
	void AddCharacterOverlay(APlayerController* InController);
	
	FORCEINLINE UHA_Overlay* GetOverlay() const { return OverlayWidget; }
};

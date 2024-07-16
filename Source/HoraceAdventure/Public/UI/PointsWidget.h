// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointsWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API UPointsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Points_Text;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* Points_Anim;
	
};

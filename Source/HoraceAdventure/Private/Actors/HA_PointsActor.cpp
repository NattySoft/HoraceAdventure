// NattySoft - All Right Reserved


#include "Actors/HA_PointsActor.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "UI/PointsWidget.h"

AHA_PointsActor::AHA_PointsActor()
{
	Widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	// Widget->SetupAttachment(GetRootComponent());
	SetRootComponent(Widget);
}

void AHA_PointsActor::BeginPlay()
{
	Super::BeginPlay();

	if (Widget && Widget->GetWidget())
	{
		UPointsWidget* PointsWidget = Cast<UPointsWidget>(Widget->GetWidget());
		PointsWidget->PlayAnimation(PointsWidget->Points_Anim);

		const FString PointsText = FString::Printf(TEXT("%d"), PointsToAdd);
		PointsWidget->Points_Text->SetText(FText::FromString(PointsText));

		const float AnimEndTime = PointsWidget->Points_Anim->GetEndTime();
		SetLifeSpan(AnimEndTime);
	}
}


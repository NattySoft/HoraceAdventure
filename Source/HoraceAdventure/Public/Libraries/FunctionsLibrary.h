// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "FunctionsLibrary.generated.h"

class AHA_Horace;
/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API UFunctionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category="Horace|Libraries", meta=(DefaultToSelf = "WorldContextObject"))
	static void PlaySoundFx(const UObject* WorldContextObject, USoundBase* SFX, float Delay = 0.f);

	UFUNCTION(Category="Horace|Libraries", meta=(DefaultToSelf = "WorldContextObject"))
	static void PlayInteractFx(const UObject* WorldContextObject, UNiagaraSystem* VFX_Niagara,
		UParticleSystem* VFX_Particle, const FVector& VFX_Location, const FVector& Scale = FVector(1.f));

	UFUNCTION(Category="Horace|Libraries")
	static AHA_Horace* GetHorace(AActor* FromActor = nullptr);

	UFUNCTION(Category="Horace|Libraries")
	static void PrintDebugMessage(const FString& DebugMessage, int32 Key = -1, float TimeToDisplay = 3.f, FColor DisplayColor = FColor::Green, bool bNewerOnTop = true, const FVector2D& TextScale = FVector2D::UnitVector);
	
};

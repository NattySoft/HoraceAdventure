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
	static void PlayBlockSoundFx(const UObject* WorldContextObject, USoundBase* SFX);

	UFUNCTION(Category="Horace|Libraries", meta=(DefaultToSelf = "WorldContextObject"))
	static void PlayBlockInteractFx(const UObject* WorldContextObject, UNiagaraSystem* VFX_Niagara, UParticleSystem* VFX_Particle, const FVector& VFX_Location);

	UFUNCTION(Category="Horace|Libraries")
	static AHA_Horace* GetHorace(AActor* FromActor = nullptr);
	
};

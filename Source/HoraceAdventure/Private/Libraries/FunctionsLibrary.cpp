// NattySoft - All Right Reserved


#include "Libraries/FunctionsLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/HA_Horace.h"
#include "Kismet/GameplayStatics.h"

void UFunctionsLibrary::PlayBlockSoundFx(const UObject* WorldContextObject, USoundBase* SFX)
{
	if (SFX)
	{
		UGameplayStatics::PlaySound2D(WorldContextObject, SFX);
	}
}

void UFunctionsLibrary::PlayBlockInteractFx(const UObject* WorldContextObject, UNiagaraSystem* VFX_Niagara, UParticleSystem* VFX_Particle, const FVector& VFX_Location)
{
	if (VFX_Niagara)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, VFX_Niagara, VFX_Location);
	}

	if (VFX_Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, VFX_Particle, VFX_Location);
	}
}

AHA_Horace* UFunctionsLibrary::GetHorace(AActor* FromActor)
{
	if (!IsValid(FromActor)) return nullptr;
	return Cast<AHA_Horace>(FromActor);
}

void UFunctionsLibrary::PrintDebugMessage(const FString& DebugMessage, int32 Key, float TimeToDisplay, FColor DisplayColor, bool bNewerOnTop, const FVector2D& TextScale)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage);
}

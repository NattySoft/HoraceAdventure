// NattySoft - All Right Reserved


#include "Libraries/FunctionsLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/HA_Horace.h"
#include "Kismet/GameplayStatics.h"


/**
 * @brief Plays a sound effect with optional delay.
 *
 * This function plays a sound effect using the specified sound base and delay. If the delay is less than or equal to 0, the sound effect will be played immediately.
 * If the delay is greater than 0, the sound effect will be played after the specified delay.
 *
 * @param WorldContextObject The object that provides the context for the world.
 * @param SFX The sound effect to be played.
 * @param Delay The delay in seconds before playing the sound effect. Default value is 0.
 */
void UFunctionsLibrary::PlaySoundFx(const UObject* WorldContextObject, USoundBase* SFX, const float Delay)
{
	if (SFX && Delay <= 0)
	{
		UGameplayStatics::PlaySound2D(WorldContextObject, SFX);
	}
	else if (SFX)
	{
		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([WorldContextObject, SFX]
		{
			UGameplayStatics::PlaySound2D(WorldContextObject, SFX);
		});
		
		FTimerHandle DelayHandler;
		const UWorld* World = Cast<UWorld>(const_cast<UObject*&>(WorldContextObject));
		if (!World) return;
		World->GetTimerManager().SetTimer(DelayHandler, TimerCallback, Delay, false);
	}
}

/**
 * @brief Plays interaction visual effects at a specified location.
 *
 * @param WorldContextObject The world context object.
 * @param VFX_Niagara The Niagara system to spawn at the specified location.
 * @param VFX_Particle The particle system to spawn at the specified location.
 * @param VFX_Location The location at which to spawn the visual effects.
 * @param Scale The scale of the visual effects.
 */
void UFunctionsLibrary::PlayInteractFx(const UObject* WorldContextObject, UNiagaraSystem* VFX_Niagara,
                                       UParticleSystem* VFX_Particle, const FVector& VFX_Location, const FVector& Scale)
{
	if (VFX_Niagara)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, VFX_Niagara, VFX_Location, FRotator::ZeroRotator, Scale);
	}

	if (VFX_Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, VFX_Particle, VFX_Location, FRotator::ZeroRotator, Scale);
	}
}

/**
 * Returns the AHA_Horace instance from the given AActor instance.
 *
 * @param FromActor The AActor instance to get the AHA_Horace instance from.
 * @return The AHA_Horace instance if it exists, nullptr otherwise.
 */
AHA_Horace* UFunctionsLibrary::GetHorace(AActor* FromActor)
{
	if (!IsValid(FromActor)) return nullptr;
	return Cast<AHA_Horace>(FromActor);
}

/**
 * @brief Prints a debug message on the screen using the OnScreenDebugMessage function.
 *
 * @param DebugMessage The message to be displayed on the screen.
 * @param Key The key used to identify the debug message.
 * @param TimeToDisplay The amount of time in seconds that the message should be displayed on the screen.
 * @param DisplayColor The color of the debug message.
 * @param bNewerOnTop If true, the newer debug message will be placed on top of the older ones.
 * @param TextScale The scale of the text in the debug message.
 */
void UFunctionsLibrary::PrintDebugMessage(const FString& DebugMessage, int32 Key, float TimeToDisplay, FColor DisplayColor, bool bNewerOnTop, const FVector2D& TextScale)
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage);
}

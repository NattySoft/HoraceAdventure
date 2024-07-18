// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HA_GameModeBase.generated.h"

class AHA_Horace;

DECLARE_MULTICAST_DELEGATE(FPlayerRespawned);

UCLASS()
class HORACEADVENTURE_API AHA_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHoraceDestroyed(AActor* DestroyedActor);
	void Respawn();
	
	UPROPERTY(EditAnywhere, Category="Horace Adventure")
	FTransform SpawnTransform;

	UPROPERTY(EditDefaultsOnly, Category="Horace Adventure")
	TSubclassOf<AHA_Horace> HoraceClass;
	
private:
	UPROPERTY()
	AHA_Horace* Horace;
	
public:
	FPlayerRespawned PlayerRespawned;
	
	FORCEINLINE void SetSpawnTransform(const FTransform& Transform) { SpawnTransform = Transform; }
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HA_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HORACEADVENTURE_API AHA_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Horace Adventure")
	FTransform SpawnTransform;

public:
	FORCEINLINE void SetSpawnTransform(const FTransform& Transform) { SpawnTransform = Transform; }
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

constexpr ECollisionChannel ECC_FireBall = ECC_GameTraceChannel1;
inline FName PBlockTag = "PBBlock";

UENUM(BlueprintType, Blueprintable)
enum EHitPoint : int32
{
	EHP_Dead = 0,
	EHP_Small = 1,
	EHP_Big = 2,
	EHP_MAX = 1
};

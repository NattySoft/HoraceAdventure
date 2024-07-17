// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_GameModeBase.h"

#include "Characters/HA_Horace.h"
#include "Controllers/HA_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AHA_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Horace = Cast<AHA_Horace>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	checkf(Horace, TEXT("AHA_GameModeBase::BeginPlay Horace is not defined"));
	checkf(HoraceClass, TEXT("AHA_GameModeBase::BeginPlay HoraceClass is not defined"));
	
	Horace->OnDestroyed.AddDynamic(this, &AHA_GameModeBase::OnHoraceDestroyed);
}

void AHA_GameModeBase::OnHoraceDestroyed(AActor* DestroyedActor)
{
	AHA_PlayerController* HoraceController = Cast<AHA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!HoraceController) return;
	if (HoraceController->GetLives() <= 0) return;
	
	FActorSpawnParameters SpawnParameters;		
	Horace = GetWorld()->SpawnActorDeferred<AHA_Horace>(HoraceClass, FTransform::Identity);
	if (Horace)
	{
		Horace = Cast<AHA_Horace>(UGameplayStatics::FinishSpawningActor(Horace, SpawnTransform));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Horace);
		Horace->OnDestroyed.AddDynamic(this, &AHA_GameModeBase::OnHoraceDestroyed);
	}
}

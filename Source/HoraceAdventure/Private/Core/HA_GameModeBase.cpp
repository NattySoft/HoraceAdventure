// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HA_GameModeBase.h"

#include "Characters/HA_Horace.h"
#include "Controllers/HA_PlayerController.h"
#include "Core/HA_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void AHA_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CarryOverGameStats();
	
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
	
	Respawn();
}

void AHA_GameModeBase::Respawn()
{
	FActorSpawnParameters SpawnParameters;		
	Horace = GetWorld()->SpawnActorDeferred<AHA_Horace>(HoraceClass, FTransform::Identity);
	if (Horace)
	{
		Horace = Cast<AHA_Horace>(UGameplayStatics::FinishSpawningActor(Horace, SpawnTransform));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Horace);
		Horace->OnDestroyed.AddDynamic(this, &AHA_GameModeBase::OnHoraceDestroyed);

		//Broadcast the respawn
		PlayerRespawned.Broadcast();
	}
}

void AHA_GameModeBase::CarryOverGameStats() const
{
	const UHA_GameInstance* GI = Cast<UHA_GameInstance>(GetGameInstance());
	check(GI);

	AHA_PlayerController* PlayerController = Cast<AHA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PlayerController);
	
	PlayerController->SetCoins(GI->Coins);
	PlayerController->SetLives(GI->Lives);
	PlayerController->SetPoints(GI->Points);
}

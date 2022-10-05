// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


// Called when the game starts or when spawned
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor) 
{
	if (DeadActor == Tank) {
		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}
		Tank->HandleDestruction();
	}
	else if (ATower* DestroyTower=Cast<ATower>(DeadActor)) {
		DestroyTower->HandleDestruction();
	}
}

void AToonTanksGameMode::HandleGameStart() {
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	StartGame();
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}






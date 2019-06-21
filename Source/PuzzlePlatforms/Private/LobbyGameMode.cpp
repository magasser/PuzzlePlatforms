// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "Engine/Engine.h"
#include "TimerManager.h"


ALobbyGameMode::ALobbyGameMode()
{
	PlayersReady = 0;
	PlayersInLobby = 0;
	DefaultGameMap = "Maps/Puzzle01";
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++PlayersInLobby;
	if (PlayersInLobby >= 3)
	{		
		FTimerHandle TimerHandle_DelayStartGame;
		GetWorldTimerManager().SetTimer(TimerHandle_DelayStartGame, this, &ALobbyGameMode::StartServerTravel, 0.f, false, 5.f);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	--PlayersInLobby;
}

void ALobbyGameMode::PlayerReadyUp()
{
	++PlayersReady;

	
}

void ALobbyGameMode::StartGame()
{
	if (PlayersReady >= PlayersInLobby)
	{
		FTimerHandle TimerHandle_DelayStartGame;
		GetWorldTimerManager().SetTimer(TimerHandle_DelayStartGame, this, &ALobbyGameMode::StartServerTravel, 0.f, false, 5.f);
	}
}

void ALobbyGameMode::StartServerTravel()
{
	if (UWorld* World = GetWorld())
	{
		const FString MapToTravelTo = FString("/Game/").Append(*DefaultGameMap).Append("?listen");

		bUseSeamlessTravel = true;
		World->ServerTravel(*MapToTravelTo);
	}
}

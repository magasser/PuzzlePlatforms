// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformsGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ALobbyGameMode : public APuzzlePlatformsGameMode
{
	GENERATED_BODY()

public:

	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	void PlayerReadyUp();

	void StartGame();

private:

	uint32 PlayersInLobby;

	UPROPERTY(EditDefaultsOnly)
	uint32 PlayersReady;

	UPROPERTY(EditDefaultsOnly)
	FString DefaultGameMap;

	UFUNCTION()
	void StartServerTravel();
	
	
};

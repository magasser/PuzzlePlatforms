// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/Menu.h"
#include "LobbyMenu.generated.h"


class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ULobbyMenu : public UMenu
{
	GENERATED_BODY()
	
	
public:

	virtual bool Initialize() override;

	virtual void Setup() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ReadyButton;

	UFUNCTION()
	void ReadyUp();

	UFUNCTION()
	void StartGame();
	
};

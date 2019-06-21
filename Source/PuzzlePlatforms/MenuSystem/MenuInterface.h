// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMS_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void Host(FString ServerName) = 0;

	virtual void Join(uint32 Index) = 0;

	virtual void OpenMainMenu() = 0;

	virtual void RefreshServerList() = 0;

	virtual void PlayerReadyUp() = 0;

	virtual void StartGame() = 0;
};

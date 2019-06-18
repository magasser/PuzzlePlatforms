// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "Menu.h"
#include "GameMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PUZZLEPLATFORMS_API UGameMenu : public UMenu
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize() override;

private:
	
	UPROPERTY(meta = (BindWidget))
	UButton* CloseMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION()
	void CloseMenu();

	UFUNCTION()
	void MainMenu();
	
};

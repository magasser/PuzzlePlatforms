// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"
#include "Components/Button.h"


bool UGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	CloseMenuButton->OnClicked.AddDynamic(this, &UGameMenu::CloseMenu);
	MainMenuButton->OnClicked.AddDynamic(this, &UGameMenu::MainMenu);

	return true;
}

void UGameMenu::CloseMenu()
{
	Teardown();
}

void UGameMenu::MainMenu()
{
	if (MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->OpenMainMenu();
	}
}

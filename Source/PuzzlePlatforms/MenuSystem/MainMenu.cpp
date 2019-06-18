// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"


bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMenu);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Teardown();
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		FString IPAddress = FString(IPAddressField->GetText().ToString());

		MenuInterface->Join(IPAddress);
	}
}

void UMainMenu::BackToMenu()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit);
}





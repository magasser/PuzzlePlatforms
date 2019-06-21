// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ServerRow.h"


UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	
}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);
	HostGameButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMenu);
	BackButton2->OnClicked.AddDynamic(this, &UMainMenu::BackToMenu);
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
		MenuInterface->Host(ServerHostName->GetText().ToString());
	}
}

void UMainMenu::SetServerList(TArray<FServerData> ServerData)
{
	if (!ensure(ServerRowWidget != nullptr)) return;

	UWorld* World = GetWorld();

	ServerList->ClearChildren();

	uint32 Index = 0;
	for (const FServerData& Data : ServerData)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowWidget);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(Data.ServerName));
		Row->HostUserName->SetText(FText::FromString(Data.HostUserName));
		Row->ConnectionFraction->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), Data.CurrentPlayers, Data.MaxPlayers)));
		Row->Setup(this, Index);
		++Index;

		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;

	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
	{
		if (UServerRow* Child = Cast<UServerRow>(ServerList->GetChildAt(i)))
		{
			Child->bIsSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

void UMainMenu::OpenJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::OpenHostMenu()
{
	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr && SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index -> %d."), SelectedIndex.GetValue());

		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No selected index."));
	}
}

void UMainMenu::BackToMenu()
{
	ServerList->ClearChildren();
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit);
}





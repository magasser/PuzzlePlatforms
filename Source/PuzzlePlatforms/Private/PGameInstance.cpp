// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PGameInstance.h"
#include "Engine/Engine.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"


UPGameInstance::UPGameInstance(const FObjectInitializer& ObjectInitializer)
{
	DefaultGameMap = FString("Maps/Puzzle01");
	DefaultMenuMap = FString("MenuSystem/MainMenu");
}

void UPGameInstance::Init()
{

}

void UPGameInstance::Quit()
{

}

void UPGameInstance::OpenMainMenu()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	APlayerController* PlayerController = GetFirstLocalPlayerController(GetWorld());
	if (!ensure(PlayerController != nullptr)) return;

	const FString MapToTravelTo = FString("/Game/").Append(*DefaultMenuMap);

	PlayerController->ClientTravel(*MapToTravelTo, ETravelType::TRAVEL_Absolute);
}

void UPGameInstance::Host()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	const FString MapToTravelTo = FString("/Game/").Append(*DefaultGameMap).Append("?listen");

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	World->ServerTravel(*MapToTravelTo);
}

void UPGameInstance::Join(const FString& Address)
{
	APlayerController* PlayerController = GetFirstLocalPlayerController(GetWorld());
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPGameInstance::LoadMenu()
{
	if (!ensure(MainMenuWidget != nullptr)) return;
	UMainMenu* MainMenu = CreateWidget<UMainMenu>(this, MainMenuWidget);

	if (!ensure(MainMenu != nullptr)) return;
	MainMenu->SetMenuInterface(this);

	MainMenu->Setup();
}

void UPGameInstance::OpenGameMenu()
{
	if (!ensure(GameMenutWidget != nullptr)) return;
	UGameMenu* GameMenu = CreateWidget<UGameMenu>(this, GameMenutWidget);

	if (!ensure(GameMenu != nullptr)) return;
	GameMenu->SetMenuInterface(this);

	GameMenu->Setup();
}

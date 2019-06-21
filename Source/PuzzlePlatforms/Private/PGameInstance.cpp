// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PGameInstance.h"
#include "Engine/Engine.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "MenuSystem/LobbyMenu.h"
#include "LobbyGameMode.h"

const static FName SESSION_NAME = TEXT("Game");
const static FName SERVER_NAME_KEY = TEXT("Servername");


UPGameInstance::UPGameInstance(const FObjectInitializer& ObjectInitializer)
{
	DefaultLobbyMap = FString("Maps/Lobby");
	DefaultMenuMap = FString("MenuSystem/MainMenu");
}

void UPGameInstance::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!ensure(Subsystem != nullptr)) return;

	UE_LOG(LogTemp, Warning, TEXT("Found subsystem -> %s"), *Subsystem->GetSubsystemName().ToString());

	SessionInterface = Subsystem->GetSessionInterface();
	if (!ensure(SessionInterface.IsValid())) return;
	
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPGameInstance::OnCreateSessionComplete);
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPGameInstance::OnDestroySessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPGameInstance::OnFindSessionsComplete);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPGameInstance::OnJoinSessionComplete);
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

void UPGameInstance::Host(FString ServerName)
{
	DesiredServerName = ServerName;

	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session!"));
		return;
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	const FString MapToTravelTo = FString("/Game/").Append(*DefaultLobbyMap).Append("?listen");

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	World->ServerTravel(*MapToTravelTo);
}

void UPGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UPGameInstance::OnFindSessionsComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && MainMenu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished Find Session."));
		TArray<FServerData> ServerData;

		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			FServerData Data;

			SearchResult.Session.SessionSettings.Get(SERVER_NAME_KEY, Data.ServerName);
			Data.HostUserName = SearchResult.Session.OwningUserName;
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections + 1;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;


			ServerData.Add(Data);
		}

		// For Testing
		//MainMenu->SetServerList({ "TestServer1", "TestServer2", "TestServer3" });
		MainMenu->SetServerList(ServerData);
	}
}

void UPGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = false;

		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 100;

		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session."));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}

}

void UPGameInstance::PlayerReadyUp()
{
	ALobbyGameMode* LobbyGameMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	if (!ensure(LobbyGameMode != nullptr)) return;

	LobbyGameMode->PlayerReadyUp();
}

void UPGameInstance::StartGame()
{
	ALobbyGameMode* LobbyGameMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	if (!ensure(LobbyGameMode != nullptr)) return;

	LobbyGameMode->StartGame();

	UE_LOG(LogTemp, Warning, TEXT("Starting Game ..."));
}

void UPGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;

		SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
		SessionSettings.NumPublicConnections = 5;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.Set(SERVER_NAME_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPGameInstance::Join(uint32 Index)
{

	if (!ensure(SessionInterface.IsValid())) return;
	if (!ensure(SessionSearch.IsValid())) return;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);	
}

void UPGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!ensure(SessionInterface.IsValid())) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string for session!"));
		return;
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController(GetWorld());
	if (!ensure(PlayerController != nullptr)) return;
	
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPGameInstance::LoadMenuWidget()
{
	if (!ensure(MainMenuWidget != nullptr)) return;
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuWidget);

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

void UPGameInstance::OpenLobbyMenu()
{
	if (!ensure(LobbyMenuWidget != nullptr)) return;
	ULobbyMenu* LobbyMenu = CreateWidget<ULobbyMenu>(this, LobbyMenuWidget);

	if (!ensure(LobbyMenu != nullptr)) return;
	LobbyMenu->SetMenuInterface(this);

	LobbyMenu->Setup();
}

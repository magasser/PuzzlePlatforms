// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuInterface.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
#include "PGameInstance.generated.h"

class UUserWidget;
class UMainMenu;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION()
	virtual void Host(FString ServerName) override;

	UFUNCTION()
	virtual void OpenMainMenu() override;

	UFUNCTION()
	virtual void Join(uint32 Index) override;

	UFUNCTION()
	virtual void RefreshServerList() override;

	UFUNCTION()
	virtual void PlayerReadyUp() override;

	UFUNCTION()
	virtual void StartGame() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void OpenGameMenu();

	UFUNCTION(BlueprintCallable)
	void OpenLobbyMenu();
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidget;

	UMainMenu* MainMenu;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameMenutWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LobbyMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Map")
	FString DefaultLobbyMap;

	UPROPERTY(EditDefaultsOnly, Category = "Menu")
	FString DefaultMenuMap;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionsComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	FString DesiredServerName;

	void CreateSession();
	
	
};

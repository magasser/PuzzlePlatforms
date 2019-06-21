// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/Menu.h"
#include "MainMenu.generated.h"


class UButton;
class UWidgetSwitcher;
class UPanelWidget;
class UEditableTextBox;

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString ServerName;
	FString HostUserName;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;

};

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class PUZZLEPLATFORMS_API UMainMenu : public UMenu
{
	GENERATED_BODY()


public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	void SetServerList(TArray<FServerData> ServerData);

	void SelectIndex(uint32 Index);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ServerRowWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton2;

	UPROPERTY(meta = (BindWidget))
	UButton* HostGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ServerHostName;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerList;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void BackToMenu();

	UFUNCTION()
	void QuitGame();

	TOptional<uint32> SelectedIndex;

	void UpdateChildren();

};
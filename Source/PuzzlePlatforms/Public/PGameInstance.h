// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuInterface.h"
#include "Engine/GameInstance.h"
#include "PGameInstance.generated.h"

class UUserWidget;

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
	virtual void Host() override;

	UFUNCTION()
		virtual void Quit() override;

	UFUNCTION()
	virtual void OpenMainMenu() override;

	UFUNCTION()
	virtual void Join(const FString& Address) override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void OpenGameMenu();

protected:

private:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameMenutWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Map")
	FString DefaultGameMap;

	UPROPERTY(EditDefaultsOnly, Category = "Menu")
	FString DefaultMenuMap;
	
	
};

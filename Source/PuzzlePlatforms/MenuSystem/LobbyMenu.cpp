// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyMenu.h"
#include "Components/Button.h"


bool ULobbyMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	ReadyButton->OnClicked.AddDynamic(this, &ULobbyMenu::ReadyUp);
	StartButton->OnClicked.AddDynamic(this, &ULobbyMenu::StartGame);

	UE_LOG(LogTemp, Warning, TEXT("Added OnClick events"));


	return true;
}

void ULobbyMenu::Setup()
{
	this->AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void ULobbyMenu::ReadyUp()
{
	ReadyButton->SetColorAndOpacity(FLinearColor::Green);
	ReadyButton->SetIsEnabled(false);

	MenuInterface->PlayerReadyUp();
}

void ULobbyMenu::StartGame()
{
}

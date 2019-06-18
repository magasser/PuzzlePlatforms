// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu.h"


bool UMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	return true;
}

void UMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	if (MenuInterface)
	{
		this->MenuInterface = MenuInterface;
	}
}

void UMenu::Setup()
{
	this->AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UMenu::Teardown()
{
	this->RemoveFromViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	const FInputModeGameOnly InputMode;

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}

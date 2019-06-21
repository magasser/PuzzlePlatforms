// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"
#include "MainMenu.h"


void UServerRow::Setup(UMainMenu* Parent, uint32 Index)
{
	this->bIsSelected = false;
	this->Index = Index;
	this->Parent = Parent;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	Parent->SelectIndex(Index);
}

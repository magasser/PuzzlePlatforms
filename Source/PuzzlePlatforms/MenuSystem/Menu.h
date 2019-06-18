// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuInterface.h"
#include "UserWidget.h"
#include "Menu.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PUZZLEPLATFORMS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();

	void Teardown();

protected:

	IMenuInterface* MenuInterface;
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

private:

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	int ActiveTriggers;

	UPROPERTY(EditAnywhere, Category = "Triggers")
	int NumberOfTriggers;

	bool bTriggered;

protected:

	/* Sets the speed at which the platform is moving */
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (MakeEditWidget = true))
	FVector TargetLocation;
	
public:
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	void AddActiveTrigger();

	void RemoveActiveTrigger();
	
	
};

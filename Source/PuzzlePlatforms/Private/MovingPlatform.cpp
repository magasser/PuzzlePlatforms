// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	bReplicates = true;
	bReplicateMovement = true;

	Speed = 0.f;

	ActiveTriggers = 0;
	NumberOfTriggers = 0;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	bTriggered = ActiveTriggers == NumberOfTriggers;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (bTriggered)
		{
			FVector Location = GetActorLocation();
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Direction * Speed * DeltaTime;
			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
	UE_LOG(LogTemp, Warning, TEXT("%d"), ActiveTriggers);

	bTriggered = ActiveTriggers == NumberOfTriggers;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers)
	{
		ActiveTriggers--;
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), ActiveTriggers);

	bTriggered = ActiveTriggers == NumberOfTriggers;
}

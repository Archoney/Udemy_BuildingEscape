// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener() : owner{ GetOwner() }
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
	actorAbleToOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto time = GetWorld()->GetTimeSeconds();
	if ( pressurePlate->IsOverlappingActor(actorAbleToOpen))
	{
		openDoor();
		doorCloseTime = time + closeDelaySeconds;
	}
	else if ( time > doorCloseTime )
	{
		closeDoor();
	}
}

void UDoorOpener::openDoor()
{
	owner->SetActorRotation(FRotator{ 0.f, openedAngle, 0.f });
}

void UDoorOpener::closeDoor()
{
	owner->SetActorRotation(FRotator{ 0.f, closedAngle, 0.f });
}


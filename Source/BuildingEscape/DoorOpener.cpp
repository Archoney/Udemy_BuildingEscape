// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto time = GetWorld()->GetTimeSeconds();

	if ( GetTotalMassOnTriggerPlate() > doorOpeningMass)
	{
		onOpen.Broadcast();
	}
	else
	{
		onClose.Broadcast();
	}
}

float UDoorOpener::GetTotalMassOnTriggerPlate() const
{
	TArray<UPrimitiveComponent*> overlappingComponents;
	check(pressurePlate && "Is an ATriggerVolume connected to the component?");
	pressurePlate->GetOverlappingComponents(overlappingComponents);

	auto totalMass{ 0.f };
	if (overlappingComponents.Num())
	{
		for (auto component : overlappingComponents)
		{
			totalMass += component->GetMass();
		}
	}

	return totalMass;
}


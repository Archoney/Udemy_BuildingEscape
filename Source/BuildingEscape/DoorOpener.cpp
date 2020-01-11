// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener() : m_owner{ GetOwner() }
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

	if (m_openingTime < m_openDuration)
	{
		m_openingTime += DeltaTime;

		if (m_openingTime > m_openDuration)
		{
			m_owner->SetActorRotation(m_openedRotation);
		}
		else
		{
			auto slerp = m_closedRotation + m_openingTime / m_openDuration * m_openedRotation;
			m_owner->SetActorRotation(slerp);
		}
	}
}


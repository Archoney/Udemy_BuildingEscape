// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	logPlayerViewPoint();
}

void UGrabber::logPlayerViewPoint()
{
	FVector outLocation;
	FRotator outRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(outLocation, outRotation);

	UE_LOG(LogTemp, Warning, TEXT("Loacation: %s\tPosition: %s"), *outLocation.ToString(), *outRotation.ToString());
}

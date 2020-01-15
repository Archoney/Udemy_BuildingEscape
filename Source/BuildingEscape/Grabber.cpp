// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/DrawDebugHelpers.h"

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

	updatePlayerViewPoint();
	traceForMovableObject();
}

void UGrabber::updatePlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
}

void UGrabber::traceForMovableObject()
{
	FHitResult traceResult;
	auto lineStart = location;
	auto lineEnd = location + reachLength * rotation.Vector();
	auto objectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	auto params = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(traceResult, lineStart, lineEnd, objectParams, params);

	auto actorHit = traceResult.GetActor();
	if (actorHit)
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *actorHit->GetName());
}
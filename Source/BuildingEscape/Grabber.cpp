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
	logPlayerViewPoint();
	drawDebugReach();
}

void UGrabber::updatePlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
}

void UGrabber::logPlayerViewPoint()
{
	UE_LOG(LogTemp, Warning, TEXT("Loacation: %s\tPosition: %s"), *location.ToString(), *rotation.ToString());
}

void UGrabber::drawDebugReach()
{
#if !defined(SHIPPING_DRAW_DEBUG_ERROR) || !SHIPPING_DRAW_DEBUG_ERROR
	auto lineStart = location;
	auto lineEnd = location + reachLength * rotation.Vector();
	auto lineColor = FColor( 255.f, 0.f, 255.f );
	DrawDebugLine(GetWorld(), lineStart, lineEnd, lineColor, false, 0.f, 0, 10.f);
#endif
}


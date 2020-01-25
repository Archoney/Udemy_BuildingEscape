// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Classes/Components/InputComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::FindPhysicsHandleComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandleComponent found in %s!"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing PhysicsHandleComponent!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent Found in %s!"), *GetOwner()->GetName());

		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing InputComponent!"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);

	FHitResult traceResult;
	auto lineStart = location;
	auto lineEnd = location + reachLength * rotation.Vector();
	auto objectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	auto params = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(traceResult, lineStart, lineEnd, objectParams, params);

	return traceResult;
}

void UGrabber::Grab()
{
	auto actorInReach = GetFirstPhysicsBodyInReach().GetActor();
	if (actorInReach)
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *actorInReach->GetName());
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release!"));
}

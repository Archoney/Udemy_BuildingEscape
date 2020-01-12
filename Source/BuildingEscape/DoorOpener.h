// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* m_owner;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(VisibleAnywhere)
	AActor* actorAbleToOpen;

	UPROPERTY(VisibleAnywhere)
	float angle{ 80.f };

	const FRotator openedRotation{ 0.f, -angle, 0.f };
	const FRotator closedRotation{ 0.f, 0.f, 0.f };
	const float openingDuration{1.f};
	float openingTime{ 0.f };
	bool openDoor{ false };
};

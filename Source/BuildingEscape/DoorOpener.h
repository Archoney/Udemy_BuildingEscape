// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenEvent);


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

	UPROPERTY(BlueprintAssignable)
		FOnOpenEvent onOpenEvent;

private:
	void openDoor();
	void closeDoor();

	float GetTotalMassOnTriggerPlate() const;

	AActor* owner;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate {	nullptr	};

	UPROPERTY(VisibleAnywhere)
	float openedAngle{ -80.f };

	UPROPERTY(VisibleAnywhere)
	float closedAngle{ 0.f };

	UPROPERTY(EditAnywhere)
	float closeDelaySeconds{ 1.0f };

	UPROPERTY(EditAnywhere)
	float doorOpeningMass{ 90.0f };

	float doorCloseTime{ 0.f };
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarChaosVehiclePawn.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOWNDELIVERYGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent();

	UPROPERTY(EditAnywhere)
		ACarChaosVehiclePawn* PlayerCar;
	UPROPERTY(EditAnywhere) 
		USoundBase* honkSound;
	UPROPERTY(EditAnywhere)
		float honkVolume = 0.5f;
private:

	void Throttle(float Value);
	void TurnCar(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void OnHandbrakePressed();
	void OnHandbrakeReleased();
	void Interact();

	void UpdateInAirControl(float DeltaTime);

	UPROPERTY()
		float CarMomentum;
	UPROPERTY()
		bool bThrottleReceived = false;
};

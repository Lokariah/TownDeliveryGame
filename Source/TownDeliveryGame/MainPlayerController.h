// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCarPawn.h"
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
		APlayerCarPawn* PlayerCar;

private:
	void Throttle(float Value);
	void TurnCar(float Value);
	void Interact();

	UPROPERTY()
		float CarMomentum;
	UPROPERTY()
		bool bThrottleReceived = false;
};

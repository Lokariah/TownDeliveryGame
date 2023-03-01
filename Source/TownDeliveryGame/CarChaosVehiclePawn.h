// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CarChaosVehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class TOWNDELIVERYGAME_API ACarChaosVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
		ACarChaosVehiclePawn();

protected:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

public:


	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	//Remnants from original implementation pre ChaosVehicleMovementComponent. Unused
	UPROPERTY(EditAnywhere)
		float Acceleration = 10.0f;
	UPROPERTY(EditAnywhere)
		float MaxSpeed = 120.0f;
	UPROPERTY(EditAnywhere)
		float TurningRadius = 45.0f;
	UPROPERTY(EditAnywhere)
		float Mass = 20.0f;

};

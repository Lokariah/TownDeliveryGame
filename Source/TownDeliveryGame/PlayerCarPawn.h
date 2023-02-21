// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCarPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOWNDELIVERYGAME_API APlayerCarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		float Acceleration = 10.0f;
	UPROPERTY(EditAnywhere)
		float MaxSpeed = 120.0f;
	UPROPERTY(EditAnywhere)
		float TurningRadius = 45.0f;
	UPROPERTY(EditAnywhere)
		float Mass = 20.0f;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CarMesh;


};

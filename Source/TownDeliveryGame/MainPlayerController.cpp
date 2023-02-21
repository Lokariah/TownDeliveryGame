// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Components/InputComponent.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PlayerCar = Cast<APlayerCarPawn>(GetPawn());
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerCar) {
		if (bThrottleReceived) {
			bThrottleReceived = false;
		}
		else {
			CarMomentum -= DeltaTime * PlayerCar->Mass;
		}
		PlayerCar->SetActorLocation(PlayerCar->GetActorLocation() + PlayerCar->GetActorForwardVector() * DeltaTime);
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis("Throttle", this, &AMainPlayerController::Throttle);
	InputComponent->BindAxis("Turn", this, &AMainPlayerController::TurnCar);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayerController::Interact);
}

void AMainPlayerController::Throttle(float Value)
{
	if (PlayerCar) {
		bThrottleReceived = true;
		CarMomentum += Value * PlayerCar->Acceleration;
	}
}

void AMainPlayerController::TurnCar(float Value)
{
	if(PlayerCar) PlayerCar->AddActorLocalRotation(FRotator(0.0f, Value * PlayerCar->TurningRadius, 0.0f));
}

void AMainPlayerController::Interact()
{
}

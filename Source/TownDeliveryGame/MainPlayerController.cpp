// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChaosWheeledVehicleMovementComponent.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PlayerCar = Cast<ACarChaosVehiclePawn>(GetPawn());
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateInAirControl(DeltaTime);

	/*if (PlayerCar) {
		if (bThrottleReceived) {
			bThrottleReceived = false;
		}
		else {
			CarMomentum -= DeltaTime * PlayerCar->Mass;
		}
		PlayerCar->SetActorLocation(PlayerCar->GetActorLocation() + PlayerCar->GetActorForwardVector() * DeltaTime);
	}*/
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis("Throttle", this, &AMainPlayerController::Throttle);
	InputComponent->BindAxis("Turn", this, &AMainPlayerController::TurnCar);
	InputComponent->BindAxis("LookRight", this, &AMainPlayerController::LookRight);
	InputComponent->BindAxis("LookUp", this, &AMainPlayerController::LookUp);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayerController::Interact);
	InputComponent->BindAction("Handbrake", IE_Pressed, this, &AMainPlayerController::OnHandbrakePressed);
	InputComponent->BindAction("Handbrake", IE_Released, this, &AMainPlayerController::OnHandbrakeReleased);
}

void AMainPlayerController::Throttle(float Value)
{
	if (PlayerCar) {
			PlayerCar->GetVehicleMovementComponent()->SetThrottleInput(Value);
			if(0 - Value >= 0) PlayerCar->GetVehicleMovementComponent()->SetBrakeInput(0 - Value);
	}
}

void AMainPlayerController::TurnCar(float Value)
{
	if (PlayerCar) PlayerCar->GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void AMainPlayerController::LookUp(float Value)
{
	if (Value != 0.0f && PlayerCar) {
		PlayerCar->AddControllerPitchInput(Value);
	}
}

void AMainPlayerController::LookRight(float Value)
{
	if (Value != 0.0f && PlayerCar) {
		PlayerCar->AddControllerYawInput(Value);
	}
}

void AMainPlayerController::OnHandbrakePressed()
{
	if (PlayerCar) PlayerCar->GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AMainPlayerController::OnHandbrakeReleased()
{
	if (PlayerCar) PlayerCar->GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AMainPlayerController::Interact()
{
	UGameplayStatics::PlaySound2D(GetWorld(), honkSound, honkVolume, 1.0f, 0.0f);
}

void AMainPlayerController::UpdateInAirControl(float DeltaTime)
{
	if (PlayerCar) {
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(PlayerCar);
		const FVector traceStart = PlayerCar->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
		const FVector traceEnd = PlayerCar->GetActorLocation() - FVector(0.0f, 0.0f, 200.0f);

		FHitResult Hit;

		const bool bInAir = !PlayerCar->GetWorld()->LineTraceSingleByChannel(Hit, traceStart, traceEnd, ECC_Visibility, queryParams);
		const bool bNotGrounded = FVector::DotProduct(PlayerCar->GetActorUpVector(), FVector::UpVector) < 0.1f;

		if (bInAir || bNotGrounded) {
			const float forwardInput = InputComponent->GetAxisValue("Throttle");
			const float rightInput = InputComponent->GetAxisValue("Turn");
			const float airMovementForcePitch = 3.0f;
			const float airMovementForceRoll = !bInAir && bNotGrounded ? 20.0f : 3.0f;

			if (UPrimitiveComponent* vehicleMesh = PlayerCar->GetVehicleMovementComponent()->UpdatedPrimitive) {
				const FVector movementVector = FVector(-rightInput * airMovementForceRoll, forwardInput * airMovementForcePitch, 0.1f) * DeltaTime * 25.0f;
				const FVector newAngularMovement = PlayerCar->GetActorRotation().RotateVector(movementVector);

				vehicleMesh->SetPhysicsAngularVelocityInDegrees(newAngularMovement, true);
			}
		}
	}
}

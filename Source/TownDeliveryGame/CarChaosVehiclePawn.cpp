// Fill out your copyright notice in the Description page of Project Settings.

#include "CarChaosVehiclePawn.h"
#include "ChaosWheeledVehicleMovementComponent.h"

ACarChaosVehiclePawn::ACarChaosVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	UChaosWheeledVehicleMovementComponent* vehicleComponent = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	SetRootComponent(GetMesh());
	vehicleComponent->EngineSetup.MaxRPM = 5700.0f;
	vehicleComponent->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	vehicleComponent->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, 400.0f);
	vehicleComponent->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1000.0f, 500.0f);
	vehicleComponent->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(5700.0f, 400.0f);

	vehicleComponent->SteeringSetup.SteeringType = ESteeringType::Ackermann;
	vehicleComponent->SteeringSetup.SteeringCurve.GetRichCurve()->Reset();
	vehicleComponent->SteeringSetup.SteeringCurve.GetRichCurve()->AddKey(0.0f, 1.0f);
	vehicleComponent->SteeringSetup.SteeringCurve.GetRichCurve()->AddKey(40.0f, 0.7f);
	vehicleComponent->SteeringSetup.SteeringCurve.GetRichCurve()->AddKey(120.0, 0.6f);

	vehicleComponent->DifferentialSetup.DifferentialType = EVehicleDifferential::AllWheelDrive;
	vehicleComponent->DifferentialSetup.FrontRearSplit = 0.65f;

	vehicleComponent->TransmissionSetup.bUseAutomaticGears = true;
	vehicleComponent->TransmissionSetup.GearChangeTime = 0.10f;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 300.0f;
	CameraSpringArm->CameraLagSpeed = 2.0f;
	CameraSpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

void ACarChaosVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACarChaosVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

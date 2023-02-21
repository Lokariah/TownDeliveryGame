// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCarPawn.h"

// Sets default values
APlayerCarPawn::APlayerCarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
	SetRootComponent(CarMesh);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 300.0f;
	CameraSpringArm->CameraLagSpeed = 2.0f;
	CameraSpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayerCarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Copyright Epic Games, Inc. All Rights Reserved.


#include "TownDeliveryGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void ATownDeliveryGameGameModeBase::ParkingSphereOverlap(bool bStart, int houseNo)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	if (bStart && houseNo == designatedHouse) 
		ParkingOverlap = true;
	else if (!bStart && houseNo == designatedHouse) 
		ParkingOverlap = false;
}

void ATownDeliveryGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//PrimaryActorTick.bCanEverTick = true;
	int currentHouse = 0;
	UPROPERTY() TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHouseActor::StaticClass(), temp);
	for (AActor* house : temp) {
		AHouseActor* House = Cast<AHouseActor>(house);
		House->SetHouseId(currentHouse);
		currentHouse++;
		Houses.Emplace(House);
	}
	TaxiBay = Cast<ATaxiBayActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATaxiBayActor::StaticClass()));

	GenerateDestination();
	playerControllerRef = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UICount = CreateWidget(GetWorld(), UIClass);
	if (UICount) UICount->AddToViewport();
}

void ATownDeliveryGameGameModeBase::Tick(float DeltaSeconds)
{
	//Super::Tick(DeltaSeconds);
	if (ParkingOverlap) {
		if (playerControllerRef->PlayerCar->GetVelocity().Length() < ParkingSpeedAllowance) {
			if (GetWorld()->GetTimerManager().IsTimerActive(TaskInfoTimer)) GetWorld()->GetTimerManager().ClearTimer(TaskInfoTimer);
			if (designatedHouse != -1) {
				UE_LOG(LogTemp, Warning, TEXT("Overlap Tick"));
				GetWorld()->GetTimerManager().ClearTimer(DeliveryTimer);
				Houses[designatedHouse]->SetIsTarget(false);
				TaxiBay->SetIsTarget(true);
				designatedHouse = -1;
				deliveriesMade++;
				TaskInfo = 2;
				GetWorld()->GetTimerManager().SetTimer(TaskInfoTimer, this, &ATownDeliveryGameGameModeBase::TaskInfoRemover, TaskTimer, false);
			}
			else GenerateDestination();
			ParkingOverlap = false;
		}
	}
}

int ATownDeliveryGameGameModeBase::GetLives()
{
	return Lives;
}

int ATownDeliveryGameGameModeBase::GetDeliveriesMade()
{
	return deliveriesMade;
}

int ATownDeliveryGameGameModeBase::GetTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(DeliveryTimer))
		return GetWorld()->GetTimerManager().GetTimerRemaining(DeliveryTimer) + 1;
	else return -1;
}

int ATownDeliveryGameGameModeBase::GetTaskInfo()
{
	return TaskInfo;
}

void ATownDeliveryGameGameModeBase::GenerateDestination()
{
	designatedHouse = FMath::RandRange(0, Houses.Num() - 1);
	Houses[designatedHouse]->SetIsTarget(true);
	TaxiBay->SetIsTarget(false);
	float destinationTimer = Houses[designatedHouse]->GetDeliveryTime();
	TaskInfo = 1;
	GetWorld()->GetTimerManager().SetTimer(DeliveryTimer, this, &ATownDeliveryGameGameModeBase::DeliveryFailed, destinationTimer - difficultyChange * deliveriesMade, false);
	GetWorld()->GetTimerManager().SetTimer(TaskInfoTimer, this, &ATownDeliveryGameGameModeBase::TaskInfoRemover, TaskTimer, false);
}

void ATownDeliveryGameGameModeBase::DeliveryFailed()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TaskInfoTimer)) GetWorld()->GetTimerManager().ClearTimer(TaskInfoTimer);
	Houses[designatedHouse]->SetIsTarget(false);
	TaxiBay->SetIsTarget(true);
	designatedHouse = -1;
	Lives--;
	if (Lives <= 0) UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevel);
	else {
		TaskInfo = 2;
		GetWorld()->GetTimerManager().SetTimer(TaskInfoTimer, this, &ATownDeliveryGameGameModeBase::TaskInfoRemover, TaskTimer, false);
	}
}

void ATownDeliveryGameGameModeBase::TaskInfoRemover()
{
	TaskInfo = 0;
}

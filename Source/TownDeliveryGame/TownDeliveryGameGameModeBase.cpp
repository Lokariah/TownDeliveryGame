// Copyright Epic Games, Inc. All Rights Reserved.


#include "TownDeliveryGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void ATownDeliveryGameGameModeBase::ParkingSphereOverlap(bool bStart, int houseNo)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	//Determines if current bay is the desired bay 
	if (bStart && houseNo == designatedHouse) 
		ParkingOverlap = true;
	else if (!bStart && houseNo == designatedHouse) 
		ParkingOverlap = false;
}

void ATownDeliveryGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	int currentHouse = 0;
	UPROPERTY() TArray<AActor*> temp;

	//Stores all houses in array for access later and assigns them ids
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

	//UI and music setup
	UICount = CreateWidget(GetWorld(), UIClass);
	if (UICount) UICount->AddToViewport();
	UGameplayStatics::PlaySound2D(GetWorld(), themeMusic, themeVolume, 1.0f, 0.0f);
}

void ATownDeliveryGameGameModeBase::Tick(float DeltaSeconds)
{
	//Checks player is parked outside correct house/taxi bay
	if (ParkingOverlap) {
		if (playerControllerRef->PlayerCar->GetVelocity().Length() < ParkingSpeedAllowance) {
			if (GetWorld()->GetTimerManager().IsTimerActive(TaskInfoTimer)) GetWorld()->GetTimerManager().ClearTimer(TaskInfoTimer);
			//House delivery logic
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
			//Taxi bay logic
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

bool ATownDeliveryGameGameModeBase::GetEndGame()
{
	return bEndgame;
}

void ATownDeliveryGameGameModeBase::GenerateDestination()
{
	//Picks random house and configures waypoint and ui behaviour
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
	//Restarts gameloop if lives remain else shows score and heads to main menu
	if (GetWorld()->GetTimerManager().IsTimerActive(TaskInfoTimer)) GetWorld()->GetTimerManager().ClearTimer(TaskInfoTimer);
	Houses[designatedHouse]->SetIsTarget(false);
	TaxiBay->SetIsTarget(true);
	designatedHouse = -1;
	Lives--;
	if (Lives <= 0) {
		bEndgame = true;
		GetWorld()->GetTimerManager().SetTimer(EndgameTimer, this, &ATownDeliveryGameGameModeBase::EndGame, EndgameTime, false);
	}
	else {
		TaskInfo = 2;
		GetWorld()->GetTimerManager().SetTimer(TaskInfoTimer, this, &ATownDeliveryGameGameModeBase::TaskInfoRemover, TaskTimer, false);
	}
}

void ATownDeliveryGameGameModeBase::TaskInfoRemover()
{
	TaskInfo = 0;
}

void ATownDeliveryGameGameModeBase::EndGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevel);
}

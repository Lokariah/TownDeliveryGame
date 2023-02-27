// Copyright Epic Games, Inc. All Rights Reserved.


#include "TownDeliveryGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATownDeliveryGameGameModeBase::ParkingSphereOverlap(bool bStart, int houseNo)
{
	if (bStart && houseNo == designatedHouse) ParkingOverlap = true;
	else if (!bStart && houseNo == designatedHouse) ParkingOverlap = false;
}

void ATownDeliveryGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	int currentHouse = 0;
	UPROPERTY() TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHouseActor::StaticClass(), temp);
	for (AActor* house : temp) {
		AHouseActor* House = Cast<AHouseActor>(house);
		House->SetHouseId(currentHouse);
		currentHouse++;
		Houses.Emplace(House);
	}
	GenerateDestination();
	playerControllerRef = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ATownDeliveryGameGameModeBase::Tick(float DeltaSeconds)
{
	if (ParkingOverlap) {
		//if (playerControllerRef->PlayerCar->GetVelocity().Length() < ParkingSpeedAllowance) {
			if (designatedHouse != -1) {
				GetWorld()->GetTimerManager().ClearTimer(DeliveryTimer);
				Houses[designatedHouse]->SetIsTarget(false);
				designatedHouse = -1;
				deliveriesMade++;
			}
			else GenerateDestination();
		//}
	}
}

void ATownDeliveryGameGameModeBase::GenerateDestination()
{
	designatedHouse = FMath::RandRange(0, Houses.Num() - 1);
	Houses[designatedHouse]->SetIsTarget(true);
	GetWorld()->GetTimerManager().SetTimer(DeliveryTimer, this, &ATownDeliveryGameGameModeBase::DeliveryFailed, baseTimer - difficultyChange * deliveriesMade, false);
}

void ATownDeliveryGameGameModeBase::DeliveryFailed()
{
	Houses[designatedHouse]->SetIsTarget(false);
	designatedHouse = -1;
	Lives--;
	if (Lives <= 0) UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevel);
}

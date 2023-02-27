// Copyright Epic Games, Inc. All Rights Reserved.


#include "TownDeliveryGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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
}

void ATownDeliveryGameGameModeBase::Tick(float DeltaSeconds)
{
	//Super::Tick(DeltaSeconds);
	if (ParkingOverlap) {
		if (playerControllerRef->PlayerCar->GetVelocity().Length() < ParkingSpeedAllowance) {
			if (designatedHouse != -1) {
				UE_LOG(LogTemp, Warning, TEXT("Overlap Tick"));
				GetWorld()->GetTimerManager().ClearTimer(DeliveryTimer);
				Houses[designatedHouse]->SetIsTarget(false);
				TaxiBay->SetIsTarget(true);
				designatedHouse = -1;
				deliveriesMade++;
			}
			else GenerateDestination();
			ParkingOverlap = false;
		}
	}
}

void ATownDeliveryGameGameModeBase::GenerateDestination()
{
	designatedHouse = FMath::RandRange(0, Houses.Num() - 1);
	Houses[designatedHouse]->SetIsTarget(true);
	TaxiBay->SetIsTarget(false);
	GetWorld()->GetTimerManager().SetTimer(DeliveryTimer, this, &ATownDeliveryGameGameModeBase::DeliveryFailed, baseTimer - difficultyChange * deliveriesMade, false);
}

void ATownDeliveryGameGameModeBase::DeliveryFailed()
{
	Houses[designatedHouse]->SetIsTarget(false);
	designatedHouse = -1;
	Lives--;
	if (Lives <= 0) UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevel);
}

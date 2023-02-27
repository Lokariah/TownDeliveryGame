// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HouseActor.h"
#include "TaxiBayActor.h"
#include "MainPlayerController.h"
#include "TownDeliveryGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWNDELIVERYGAME_API ATownDeliveryGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void ParkingSphereOverlap(bool bStart, int houseNo);
	void Tick(float DeltaSeconds);
protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;

private:
	void GenerateDestination();
	void DeliveryFailed();

	UPROPERTY()
		int designatedHouse = -5;
	UPROPERTY()
		FTimerHandle DeliveryTimer;
	UPROPERTY(EditAnywhere)
		float baseTimer = 60.0f;
	UPROPERTY(EditAnywhere)
		float difficultyChange = 1.25f;
	UPROPERTY(EditAnywhere)
		float ParkingSpeedAllowance = 5.0f;
	UPROPERTY(EditAnywhere)
		int Lives = 3;
	UPROPERTY()
		int deliveriesMade = 0;


	UPROPERTY()
		bool ParkingOverlap = false;


	UPROPERTY()
		AMainPlayerController* playerControllerRef;

	UPROPERTY()
		TArray<AHouseActor*> Houses;

	UPROPERTY()
		ATaxiBayActor* TaxiBay;

	UPROPERTY(EditAnywhere)
		FName MainMenuLevel;
};

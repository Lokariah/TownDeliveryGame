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

	//UI related functions
	UFUNCTION(BlueprintPure)
		int GetLives();
	UFUNCTION(BlueprintPure)
		int GetDeliveriesMade();
	UFUNCTION(BlueprintPure)
		int GetTimer();
	UFUNCTION(BlueprintPure)
		int GetTaskInfo();
	UFUNCTION(BlueprintCallable)
		bool GetEndGame();

protected:
	virtual void BeginPlay() override;

private:
	//Selects random house and runs ui related params  
	void GenerateDestination();
	//Handles life logic and related ui
	void DeliveryFailed();
	//Removes task details from screen
	void TaskInfoRemover();
	//Switches level
	void EndGame();

	//Tracks house to check collisions outside, -1 = taxi bay
	UPROPERTY()
		int designatedHouse = -5;

	//Timer governing journey length
	UPROPERTY()
		FTimerHandle DeliveryTimer;
	UPROPERTY(EditAnywhere)
		float baseTimer = 60.0f;

	//Timer governing objective info appearance
	UPROPERTY()
		FTimerHandle TaskInfoTimer;
	UPROPERTY(EditAnywhere)
		float TaskTimer = 5.0f;

	//Timer governing final score appearance
	UPROPERTY()
		FTimerHandle EndgameTimer; 
	UPROPERTY(EditAnywhere)
		float EndgameTime = 5.0f;
	UPROPERTY()
		bool bEndgame = false;

	//Timer removed from delivery timer each successful run
	UPROPERTY(EditAnywhere)
		float difficultyChange = 1.25f;

	//Minimal speed to trigger parked behaviour
	UPROPERTY(EditAnywhere)
		float ParkingSpeedAllowance = 5.0f;

	UPROPERTY(EditAnywhere)
		int Lives = 3;
	UPROPERTY()
		int deliveriesMade = 0;

	//Governs which objective appears, 0 = none, 1 = drop off, 2 = pick up
	UPROPERTY()
		int TaskInfo = 0;

	UPROPERTY()
		bool ParkingOverlap = false;

	UPROPERTY()
		AMainPlayerController* playerControllerRef;

	//Need to notify waypoint display and grab journey length
	UPROPERTY()
		TArray<AHouseActor*> Houses;
	UPROPERTY()
		ATaxiBayActor* TaxiBay;

	//Used to load main menu
	UPROPERTY(EditAnywhere)
		FName MainMenuLevel;

	//UI related
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget>UIClass;
	UPROPERTY()
		UUserWidget* UICount;

	//Background music related
	UPROPERTY(EditAnywhere)
		USoundBase* themeMusic;
	UPROPERTY(EditAnywhere)
		float themeVolume = 0.5f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "HouseActor.generated.h"

class ATownDeliveryGameGameModeBase;
UCLASS()
class TOWNDELIVERYGAME_API AHouseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHouseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Used to check if car is stationary outside drop off
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Functions required to automate and run destinations of deliveries
	void SetHouseId(int id);
	int GetHouseId();

	//Allows for in editor tuning of deliveries difficulty
	float GetDeliveryTime();


	//WaypointBehaviourFunctions
	void SetIsTarget(bool bTarget);
	UFUNCTION(BlueprintPure)
		bool GetIsTarget();
private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* HouseMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* ParkingCollisionBox;

	//Unique to individual house for tracking of mission objective
	UPROPERTY(EditAnywhere)
		int HouseId = -1;

	//Editor difficulty scalar
	UPROPERTY(EditAnywhere)
		float DeliveryTime = -1.0f;

	//Triggers waypoint visualisation
	UPROPERTY()
		bool IsTarget = false;

	UPROPERTY()
		ATownDeliveryGameGameModeBase* GameModeRef;
};

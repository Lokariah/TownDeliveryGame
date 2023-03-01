// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TaxiBayActor.generated.h"

class ATownDeliveryGameGameModeBase;
UCLASS()
class TOWNDELIVERYGAME_API ATaxiBayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaxiBayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Waypoint functionality
	void SetIsTarget(bool bTarget);
	UFUNCTION(BlueprintPure)
		bool GetIsTarget();

	//Used to check if car is stationary outside pick up
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TaxiStationMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* ParkingCollisionBox;

	//Waypoint visibility tracking
	UPROPERTY()
		bool IsTarget = false;

	UPROPERTY()
		ATownDeliveryGameGameModeBase* GameModeRef;
};

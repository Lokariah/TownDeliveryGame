// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseActor.h"
#include "TownDeliveryGameGameModeBase.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AHouseActor::AHouseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HouseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House Mesh"));
	SetRootComponent(HouseMesh);
	ParkingCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Parking Collision Box"));
	ParkingCollisionBox->SetupAttachment(RootComponent);
	ParkingCollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AHouseActor::BeginPlay()
{
	Super::BeginPlay();
	ParkingCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHouseActor::OnOverlapBegin);
	ParkingCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AHouseActor::OnOverlapEnd);
	GameModeRef = Cast<ATownDeliveryGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AHouseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameModeRef->Tick(DeltaTime);
}

void AHouseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	GameModeRef->ParkingSphereOverlap(true, HouseId);
}

void AHouseActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GameModeRef->ParkingSphereOverlap(false, HouseId);
}

void AHouseActor::SetHouseId(int id)
{
	HouseId = id;
}

int AHouseActor::GetHouseId()
{
	return HouseId;
}

void AHouseActor::SetIsTarget(bool bTarget)
{
	IsTarget = bTarget;
}

bool AHouseActor::GetIsTarget()
{
	return IsTarget;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TaxiBayActor.h"
#include "TownDeliveryGameGameModeBase.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
ATaxiBayActor::ATaxiBayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TaxiStationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Taxi Station Mesh"));
	SetRootComponent(TaxiStationMesh);
	ParkingCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Parking Collision Box"));
	ParkingCollisionBox->SetupAttachment(RootComponent);
	ParkingCollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ATaxiBayActor::BeginPlay()
{
	Super::BeginPlay();
	ParkingCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATaxiBayActor::OnOverlapBegin);
	ParkingCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATaxiBayActor::OnOverlapEnd);
	GameModeRef = Cast<ATownDeliveryGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ATaxiBayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaxiBayActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	GameModeRef->ParkingSphereOverlap(true, -1);
}

void ATaxiBayActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GameModeRef->ParkingSphereOverlap(false, -1);
}


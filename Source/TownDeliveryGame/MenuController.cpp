// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuController.h"

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	//Disabled controls and allows menu interaction
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

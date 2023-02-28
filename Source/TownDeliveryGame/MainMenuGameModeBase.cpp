// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);
	if (MainMenuCount) MainMenuCount->AddToViewport();
}

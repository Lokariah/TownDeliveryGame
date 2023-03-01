// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWNDELIVERYGAME_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget>MainMenuClass;
	UPROPERTY()
		UUserWidget* MainMenuCount;
	UPROPERTY(EditAnywhere)
		USoundBase* themeMusic;
	UPROPERTY(EditAnywhere)
		float themeVolume = 0.5f;
};

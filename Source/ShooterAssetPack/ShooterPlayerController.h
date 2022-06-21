// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	void ShowWaveText();

private:
	void HideWaveText();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WaveScreen;
	
	UPROPERTY(EditAnywhere)
	float RestartTime = 5;
	
	FTimerHandle RestartTimer;

	UPROPERTY()
	UUserWidget* HUDWidget;

	UPROPERTY()
	UUserWidget* WaveWidget;

	UPROPERTY(EditDefaultsOnly)
	float HideWaveTime;

	FTimerHandle HideWaveHandle;


};

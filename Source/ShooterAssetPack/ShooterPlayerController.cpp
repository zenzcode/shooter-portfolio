// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"

void AShooterPlayerController::BeginPlay() {
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUDScreen, TEXT("Hud"));
	HUDWidget->AddToViewport();
	ShowWaveText();
}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (!HUDWidget) return;
	HUDWidget->RemoveFromViewport();

	if (bIsWinner) {
		UUserWidget* WinnerWidget = CreateWidget(this, WinScreen, TEXT("Lose Widget"));

		if (!WinnerWidget) return;
		WinnerWidget->AddToViewport();
	}
	else {
		UUserWidget* LoseWidget = CreateWidget(this, LoseScreen, TEXT("Lose Widget"));

		if (!LoseWidget) return;
		LoseWidget->AddToViewport();
	}


	GetWorld()->GetTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::RestartLevel, RestartTime, false);
}

void AShooterPlayerController::ShowWaveText() {
	WaveWidget = CreateWidget(this, WaveScreen, TEXT("Wave Widget"));

	if (!WaveWidget) return;
	if (WaveWidget->IsVisible()) {
		WaveWidget->RemoveFromViewport();
	}

	WaveWidget->AddToViewport();

	GetWorld()->GetTimerManager().SetTimer(HideWaveHandle, this, &AShooterPlayerController::HideWaveText, HideWaveTime, false);
	
}

void AShooterPlayerController::HideWaveText() {
	if (!WaveWidget) return;
	WaveWidget->RemoveFromViewport();
}
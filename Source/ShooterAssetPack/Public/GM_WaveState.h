// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GM_WaveState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AGM_WaveState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGM_WaveState();

	UFUNCTION(BlueprintCallable)
	uint8 GetWaveNumber();
	uint8 GetSpawnAddition();
	uint8 GetMaxWaves();
	void NewWave();

public:
	UPROPERTY(EditDefaultsOnly)
	uint8 maxWaves;

protected:
	virtual void BeginPlay() override;

private:
	uint8 waveNumber;
	const uint8 spawnAdditionPerWave = 8;
};

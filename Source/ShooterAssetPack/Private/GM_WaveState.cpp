// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_WaveState.h"

AGM_WaveState::AGM_WaveState() {
	waveNumber = 1;
}

void AGM_WaveState::BeginPlay() {

}

uint8 AGM_WaveState::GetWaveNumber() {
	return waveNumber;
}


uint8 AGM_WaveState::GetSpawnAddition() {
	return spawnAdditionPerWave;
}


uint8 AGM_WaveState::GetMaxWaves() {
	return maxWaves;
}

void AGM_WaveState::NewWave() {
	waveNumber++;
}
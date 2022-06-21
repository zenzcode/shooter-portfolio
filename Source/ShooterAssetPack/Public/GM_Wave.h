// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Wave.generated.h"

#define OUT
/**
 * 
 */


class ASpawnBoundingBox;
class AGM_WaveState;

UCLASS()
class SHOOTERASSETPACK_API AGM_Wave : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_Wave();

	void PawnKilled(APawn* pawn);
	
protected:
	virtual void BeginPlay() override;

private:
	void SpawnWave();

	void CheckForNewWave();

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AShooterCharacter> ShooterCharacter;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<class ASpawnBoundingBox>> SpawnPoints;

private:
	AGM_WaveState* WaveState = nullptr;
};

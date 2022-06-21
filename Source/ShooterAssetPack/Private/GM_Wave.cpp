// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Wave.h"
#include "GM_WaveState.h"

#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"
#include "SpawnBoundingBox.h"	
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

#include "Kismet/GameplayStatics.h"
#include "../ShooterAIController.h"
#include "../ShooterPlayerController.h"
#include "../ShooterCharacter.h"
#include "DrawDebugHelpers.h"

AGM_Wave::AGM_Wave() {

}

void AGM_Wave::BeginPlay() {
	PrimaryActorTick.bCanEverTick = false;
	SpawnWave();
}

void AGM_Wave::SpawnWave() {
	WaveState = GetGameState<AGM_WaveState>();
	if (!WaveState) return;

	const uint8 SpawnAmountThisWave = WaveState->GetWaveNumber() + WaveState->GetSpawnAddition();



	FActorSpawnParameters SpawnParams = {};
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Spawn x enemies
	for (size_t i = 0; i < SpawnAmountThisWave; ++i) {
		const uint8 SpawnPoint = FMath::RandRange(0, SpawnPoints.Num() - 1);
		const ASpawnBoundingBox* SpawnBox = SpawnPoints[SpawnPoint].Get();
		const FVector SpawnOrigin = SpawnBox->GetTransform().GetLocation();
		const FVector SpawnExtent = SpawnBox->GetTransform().GetScale3D();

		FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
		//Create Transform
		FTransform EnemyTransform = {};
		EnemyTransform.SetLocation(Location);

		//Spawn Actor
		AActor* EnemyActor = GetWorld()->SpawnActor<AShooterCharacter>(ShooterCharacter, EnemyTransform, SpawnParams);
		
	}
}

void AGM_Wave::PawnKilled(APawn* Pawn) {
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	if (PlayerController != nullptr) {
		//We Lost
		PlayerController->GameHasEnded();
	}
	else {
		//enemy dead
		bool bEnemyAlive = false;
		for (TActorIterator<AController> ActorIt(GetWorld()); ActorIt; ++ActorIt) {
			AController* ActiveController = *ActorIt;
			if (AShooterAIController* AiController = Cast<AShooterAIController>(ActiveController)) {
				AShooterCharacter* AiCharacter = Cast<AShooterCharacter>(AiController->GetPawn());
				if (!AiCharacter) continue;

				if (!AiCharacter->IsPlayerDead()) {
					bEnemyAlive = true;
					break;
				}
			}
		}
		if (!bEnemyAlive) {
			CheckForNewWave();
		}

		AShooterCharacter* LivingPlayer = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!LivingPlayer) return;
		LivingPlayer->AddHealth();
	}
}

void AGM_Wave::CheckForNewWave() {
	UE_LOG(LogTemp, Warning, TEXT("Checking for new wave"));
	if (!WaveState) return;
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	WaveState->NewWave();
	if (WaveState->GetWaveNumber() > WaveState->GetMaxWaves()) {
		if (!PlayerController) return;
		PlayerController->GameHasEnded(nullptr, true);
		return;
	}

	PlayerController->ShowWaveText();
	SpawnWave();
}
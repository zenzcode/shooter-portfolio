// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!AIBehavior) return;
	RunBehaviorTree(AIBehavior);

	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());

}

void AShooterAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	SetPawn(InPawn);
	if (GetBlackboardComponent()) {
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartPosition"), InPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const {
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (!ControlledCharacter) return true;

	return ControlledCharacter->IsPlayerDead();
}
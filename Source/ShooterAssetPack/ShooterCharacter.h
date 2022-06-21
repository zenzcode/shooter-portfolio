// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

#define OUT

class AGun;
UCLASS()
class SHOOTERASSETPACK_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shoot();
	void AddHealth();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void DestroyCharacter();

	UFUNCTION(BlueprintPure)
	bool IsPlayerDead() const;

	UFUNCTION(BlueprintPure)
	float GetPlayerHealth() const;

	UFUNCTION(BlueprintPure)
	bool IsPlayer() const;

private:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void LookUpRate(float Axis);
	void LookRightRate(float Axis);


	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunComponent;

	UPROPERTY()
	AGun* Gun = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float HealthIncreaseKill = 10.f;

	UPROPERTY(VisibleAnywhere)
	bool HasDied = false;

	UPROPERTY(EditDefaultsOnly)
	float DestroyTimer = 3.f;

	FTimerHandle DestroyHandle;
};

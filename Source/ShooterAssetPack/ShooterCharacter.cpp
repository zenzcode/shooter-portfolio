// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Public/GM_Wave.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGun>(GunComponent);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	Health = MaxHealth;
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);

}

void AShooterCharacter::MoveForward(float Axis) {
	AddMovementInput(GetActorForwardVector() * Axis);
}

void AShooterCharacter::MoveRight(float Axis) {
	AddMovementInput(GetActorRightVector() * Axis);
}

void AShooterCharacter::LookUpRate(float Axis) {
	AddControllerPitchInput(Axis * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float Axis) {
	AddControllerYawInput(Axis * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() {
	if (!Gun) return;
	Gun->PullTrigger();
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageApplied;

	if (Health <= 0) {
		Health = 0;
	}

	if (IsPlayerDead() && !HasDied) {
		AGM_Wave* GameMode = Cast<AGM_Wave>(GetWorld()->GetAuthGameMode());
		GameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &AShooterCharacter::DestroyCharacter, DestroyTimer, false);
		HasDied = true;
	}

	return DamageApplied;
}

void AShooterCharacter::DestroyCharacter() {
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	Destroy();
}

void AShooterCharacter::AddHealth() {
	Health = FMath::Clamp<float>(Health + HealthIncreaseKill, 0.f, MaxHealth);

}

bool AShooterCharacter::IsPlayerDead() const{
	return Health <= 0;
}

float AShooterCharacter::GetPlayerHealth() const {
	return Health / MaxHealth;
}

bool AShooterCharacter::IsPlayer() const {
	return this == UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
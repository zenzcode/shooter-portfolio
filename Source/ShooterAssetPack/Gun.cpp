// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));
	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(HitResult, ShotDirection);
	if (bSuccess) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location);	
		AController* OwnerController = GetOwnerController();
		AActor* HitActor = HitResult.GetActor();
		if (!HitActor) return;

		FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}
} 


bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) {
	 
	AController* OwnerController = GetOwnerController();

	if (OwnerController == nullptr) {
		return false;
	}

	FVector ViewLocation;
	FRotator ViewRotation;

	OwnerController->GetPlayerViewPoint(OUT ViewLocation, OUT ViewRotation);
	ShotDirection = -ViewRotation.Vector();

	FVector End = ViewLocation + ViewRotation.Vector() * Distance;

	FCollisionQueryParams CollisionSettings;
	CollisionSettings.AddIgnoredActor(this);
	CollisionSettings.AddIgnoredActor(GetOwner());


	return GetWorld()->LineTraceSingleByChannel(OUT Hit, ViewLocation, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionSettings);
}

AController* AGun::GetOwnerController() const {
	APawn* OwnerActor = Cast<APawn>(GetOwner());
	if (!OwnerActor) return nullptr;

	return OwnerActor->GetController();
}
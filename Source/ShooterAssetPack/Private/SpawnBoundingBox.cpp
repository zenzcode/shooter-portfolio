// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBoundingBox.h"	
#include "DrawDebugHelpers.h"

// Sets default values
ASpawnBoundingBox::ASpawnBoundingBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ASpawnBoundingBox::ShouldTickIfViewportsOnly() const {
	return true;
}

void ASpawnBoundingBox::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (WITH_EDITOR) {

		FVector location = GetTransform().GetLocation();
		FVector extent = GetTransform().GetScale3D();

		DrawDebugBox(GetWorld(), location, extent, FColor::Cyan);
	}

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SpringWheel.h"
#include "SpawnPoint.h"

TArray<ASpringWheel*> UTankTrack::GetWheels() const
{
	TArray<ASpringWheel*> ResultArray;
	TArray<USceneComponent*> Cheldren;
	GetChildrenComponents(true, Cheldren);
	for (auto Child : Cheldren)
	{
		USpawnPoint* ChildSpawnPoint = Cast<USpawnPoint>(Child);
		if (!ChildSpawnPoint) { continue; }
		AActor* SpawnedChild = ChildSpawnPoint->GetSpawnedActor();
		ASpringWheel* Wheel = Cast<ASpringWheel>(SpawnedChild);
		if (!Wheel) { continue; }

		ResultArray.Add(Wheel);
	}

	return ResultArray;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float ClampedThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	MoveTrack(ClampedThrottle);
}

void UTankTrack::MoveTrack(float CurrentThrottle)
{
	float ForceToApply = CurrentThrottle * TrackMaxForce;
	TArray<ASpringWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceToApply / Wheels.Num();

	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

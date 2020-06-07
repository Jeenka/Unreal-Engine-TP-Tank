// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::TurnBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -MaxDegreesPerSecond, MaxDegreesPerSecond);
	float NewRotation = RelativeSpeed * GetWorld()->DeltaTimeSeconds;
	NewRotation = FMath::Clamp<float>(RelativeRotation.Pitch + NewRotation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewRotation, 0, 0));
}
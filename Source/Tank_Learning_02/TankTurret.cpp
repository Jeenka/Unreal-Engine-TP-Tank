// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::TurnTurret(float RelativeSpeed)
{
	/*RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -MaxDegreesPerSecond, MaxDegreesPerSecond);
	float NewRotation = RelativeSpeed * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0, RelativeRotation.Yaw + NewRotation, 0));*/

	float MaxLimitedAngle = MaxDegreesPerSecond * FMath::Sign(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0.0f,
		FMath::Abs(RelativeSpeed) > FMath::Abs(MaxLimitedAngle) ?
		RelativeRotation.Yaw + MaxLimitedAngle :
		RelativeRotation.Yaw + RelativeSpeed,
		0.0f));
}
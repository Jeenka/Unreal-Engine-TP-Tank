// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_LEARNING_02_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Input)
		void MoveForward(float Direction);

	UFUNCTION(BlueprintCallable, Category = Input)
		void MoveRight(float Direction);

	UFUNCTION(BlueprintCallable, Category = Input)
		void SetTankTracks(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankTrack* RightTrack{ nullptr };
	UTankTrack* LeftTrack{ nullptr };

};

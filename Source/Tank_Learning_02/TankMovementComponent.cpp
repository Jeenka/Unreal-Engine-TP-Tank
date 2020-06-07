// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::MoveForward(float Direction)
{
	if (!ensure(RightTrack && LeftTrack)) { return; }
	RightTrack->SetThrottle(Direction);
	LeftTrack->SetThrottle(Direction);
}

void UTankMovementComponent::MoveRight(float Direction)
{
	if (!ensure(RightTrack && LeftTrack)) { return; }
	RightTrack->SetThrottle(-Direction);
	LeftTrack->SetThrottle(Direction);
}

void UTankMovementComponent::SetTankTracks(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIPathfindingDirection = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float AIForwardMove = FVector::DotProduct(AIPathfindingDirection, TankForward);
	float AIRightMove = -FVector::CrossProduct(AIPathfindingDirection, TankForward).Z; //Minus because valuse will become 1 if direction is to the right

	MoveForward(AIForwardMove);
	MoveRight(AIRightMove);
}

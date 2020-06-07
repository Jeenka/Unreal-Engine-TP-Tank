// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingCOmponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation{};

	if (GetSightHitLocation(OutHitLocation))
	{
		AimingComponent->AimTank(OutHitLocation);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Can't reach any target"));
	}
}

bool ATankPlayerController::GetSightHitLocation(FVector& OutHitLocation) const
{
	FHitResult OutHit;

	//FVector SightStart;
	//FRotator SightDirection;
	//this->GetPlayerViewPoint(SightStart, SightDirection);

	//UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *SightDirection.Vector().ToString());
	//FVector LineTraceEnd = SightStart + SightDirection.Vector() * Distance;

	//DrawDebugLine(GetWorld(), SightStart, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0, 2.5f);
	//bool IsHitting = GetWorld()->LineTraceSingleByChannel(OutHit, SightStart, LineTraceEnd, ECC_Visibility);

	//UE_LOG(LogTemp, Warning, TEXT("111Target location: %s"), *OutHit.Location.ToString());
	///--------------------------------------------------------------------------------------------

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairPosition{ ViewportSizeX * CrosshairPositionX, ViewportSizeY * CrosshairPositionY };
	FVector TraceScreenStart;
	FVector TraceScreenDirection;
	DeprojectScreenPositionToWorld(CrosshairPosition.X, CrosshairPosition.Y, TraceScreenStart, TraceScreenDirection);
	bool IsHitting = GetWorld()->LineTraceSingleByChannel(OutHit, TraceScreenStart, TraceScreenStart + TraceScreenDirection * Distance, ECC_Camera);

	if (IsHitting)
	{
		OutHitLocation = OutHit.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Aim found"));
	}
	else
	{
		OutHitLocation = TraceScreenStart + TraceScreenDirection * Distance;
		//UE_LOG(LogTemp, Warning, TEXT("Aim not found, aiming to the end of line"));
	}

	return true;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* ControlledTank = Cast<ATank>(InPawn);
		if (!ensure(ControlledTank)) { return; }

		ControlledTank->TankDestroyed.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

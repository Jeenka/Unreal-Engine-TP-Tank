// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimTank(FVector AimLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	FVector OutLaunchVelocity{ 0 };
	FVector StartLocation = Barrel->GetSocketLocation(FName{ "Projectile" });

	bool IsTraceSuccess = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (IsTraceSuccess)
	{
		LauncDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(LauncDirection);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Aimung position is unaccessible"));
	}
}

void UTankAimingComponent::SetBarrelAndTurret(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return TankFiringStatus;
}

int32 UTankAimingComponent::GetAmmoLeft() const
{
	return Ammo;
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = Direction.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;
	Barrel->TurnBarrel(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->TurnTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->TurnTurret(-DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	return !Barrel->GetForwardVector().Equals(LauncDirection, 0.01);
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo <= 0)
	{
		TankFiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		TankFiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		TankFiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		TankFiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

	if (TankFiringStatus == EFiringStatus::Locked || TankFiringStatus == EFiringStatus::Aiming)
	{
		if (!ensure(ProjectileBlueprint)) { return; }
		LastFireTime = FPlatformTime::Seconds();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		Ammo--;
	}
}


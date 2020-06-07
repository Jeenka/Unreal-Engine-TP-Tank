// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FMath::RoundToInt(DamageAmount);
	int32 DamageToTake = FMath::Clamp<int32>(DamagePoints, 0, CurrentTankHealth);
	CurrentTankHealth -= DamageToTake;
	if (CurrentTankHealth <= 0)
	{
		TankDestroyed.Broadcast();
	}
	return DamageToTake;
}

float ATank::GetHealthPrecent() const
{
	return (float)CurrentTankHealth / (float)MaxTankHealth;
}

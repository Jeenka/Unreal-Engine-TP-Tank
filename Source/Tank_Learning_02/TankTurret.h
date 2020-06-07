// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_LEARNING_02_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void TurnTurret(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond{ 40 };
	
};

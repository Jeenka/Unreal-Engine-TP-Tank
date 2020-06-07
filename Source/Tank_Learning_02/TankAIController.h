// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANK_LEARNING_02_API ATankAIController : public AAIController
{
	GENERATED_BODY()
		
protected:

	APawn* PlayerTank;
	UTankAimingComponent* AimingComponent;

	UPROPERTY(EditAnywhere)
	float PathfindingStopRadius{ 1000 };
	
private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossessedTankDeath();
	
};

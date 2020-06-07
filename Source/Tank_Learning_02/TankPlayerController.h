// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
class ATank;

UCLASS()
class TANK_LEARNING_02_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingCOmponent(UTankAimingComponent* AimingCompRef);

	UPROPERTY(EditDefaultsOnly)
		float Distance{ 1000 };

	UPROPERTY(EditDefaultsOnly)
		float CrosshairPositionX{ 0.5f };

	UPROPERTY(EditDefaultsOnly)
		float CrosshairPositionY{ 0.5f };

	UTankAimingComponent* AimingComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void AimTowardsCrosshair();
	bool GetSightHitLocation(FVector& OutHitLocation) const;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossessedTankDeath();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_LEARNING_02_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimTank(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();

	UFUNCTION(BlueprintCallable, Category = Input)
		void SetBarrelAndTurret(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = Setup)
		int32 GetAmmoLeft() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus TankFiringStatus = EFiringStatus::Reloading;

	virtual void BeginPlay() override;

private:

	UTankBarrel* Barrel{ nullptr };
	UTankTurret* Turret{ nullptr };
	FVector LauncDirection{};

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed{ 5000 };

	void MoveBarrelTowards(FVector Direction);

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime{ 3 };

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		int32 Ammo{ 5 };

	double LastFireTime{ 0 };

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};

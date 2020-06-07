// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class TANK_LEARNING_02_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttachmentSetup();

private:
	
	float ForceToApply{ 0 };

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* Spring { nullptr };

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Axle { nullptr };

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* AxleTwistConstraint { nullptr };

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Wheel { nullptr };

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(Spring);

	AxleTwistConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Twist Constraint"));
	AxleTwistConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASpringWheel::OnHit);
	AttachmentSetup();
}

void ASpringWheel::AttachmentSetup()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	Spring->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleTwistConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASpringWheel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceToApply);
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForceToApply = 0;
}

void ASpringWheel::AddDrivingForce(float ForceMagnitude)
{
	ForceToApply += ForceMagnitude;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		auto Target = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(Target, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	auto PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if (HasHit)
	{
		auto HitComponent = HitResult.GetComponent();
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
				HitComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation() //
		);
	}
}

void UGrabber::Release()
{
	auto PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	auto GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabbedComponent != nullptr)
	{
		GrabbedComponent->GetOwner()->Tags.Remove("Grabbed");
		GrabbedComponent->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent *UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent *PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires UPhysicsHandleComponent."));
	}

	return PhysicsHandle;
}

bool UGrabber::GetGrabbableInReach(FHitResult &OutHitResult) const {
	UWorld *World = GetWorld();
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * GrabDistance;

	// DrawDebugLine(World, Start, End, FColor::Red);
	// DrawDebugSphere(World, End, 10, 10, FColor::Blue, false, 5);

	return World->SweepSingleByChannel(
			OutHitResult,
			Start, End,
			FQuat::Identity,
			ECC_GameTraceChannel2,
			FCollisionShape::MakeSphere(GrabRadius) //
	);
}

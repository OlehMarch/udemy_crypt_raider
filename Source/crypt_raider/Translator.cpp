// Fill out your copyright notice in the Description page of Project Settings.

#include "Translator.h"

// Sets default values for this component's properties
UTranslator::UTranslator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTranslator::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetOwner()->GetActorLocation();
	TargetLocation = InitialLocation + Offset;
	Speed = FVector::Distance(InitialLocation, TargetLocation) / MoveTime;
}

// Called every frame
void UTranslator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor *Owner = GetOwner();
	FVector CurrentLocation = Owner->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, ShouldMove ? TargetLocation : InitialLocation, DeltaTime, Speed);
	Owner->SetActorLocation(NewLocation);
}

void UTranslator::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

bool UTranslator::GetShouldMove() const {
	return ShouldMove;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
  PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
  Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (Translator == nullptr) {
    return;
  }

  AActor *Actor = GetExpectedActor();
  if (Actor != nullptr)
  {
    // ! Not working in UE 5.1
    // auto Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
    // if (Component != nullptr) {
    //   Component->SetSimulatePhysics(false);
    // }
    Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
    Translator->SetShouldMove(true);
  }
  else
  {
    Translator->SetShouldMove(false);
  }
}

void UTriggerComponent::SetTranslator(UTranslator* NewTranslator) {
  Translator = NewTranslator;
}

AActor *UTriggerComponent::GetExpectedActor() const
{
  TArray<AActor *> Actors;
  GetOverlappingActors(Actors);

  for (AActor *Actor : Actors)
  {
    if (Actor->ActorHasTag(ExpectedActorTag) && !Actor->ActorHasTag("Grabbed"))
    {
      return Actor;
    }
  }

  return nullptr;
}

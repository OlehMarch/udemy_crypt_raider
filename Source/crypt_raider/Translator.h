// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Translator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_RAIDER_API UTranslator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTranslator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	UFUNCTION(BlueprintCallable)
	void SetShouldMove(bool ShouldMove);
	UFUNCTION(BlueprintCallable)
	bool GetShouldMove() const;

private:
	UPROPERTY(EditAnywhere, Category = "Mover")
	FVector Offset;
	UPROPERTY(EditAnywhere, Category = "Mover")
	float MoveTime = 4;
	UPROPERTY(VisibleAnywhere, Category = "Mover")
	bool ShouldMove = false;
	UPROPERTY(VisibleAnywhere, Category = "Mover")
	float Speed;

	FVector InitialLocation;
	FVector TargetLocation;
};

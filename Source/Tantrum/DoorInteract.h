// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"

#include "DoorInteract.generated.h"


class ATriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANTRUM_API UDoorInteract : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere)
	FVector MovementVector = FVector::Zero();
	UPROPERTY(EditAnywhere)
	bool ResetIfLeaveTrigger = false;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;
	FVector StartLocation = FVector::Zero();
	FVector FinalLocation = FVector::Zero();
	
	

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0F;
	UPROPERTY(EditAnywhere)
	float TimeToReturn = 1.0F;

	float CurrentRotationTime = 0.0F;
	float CurrentReturnTime = 0.0F;




public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere)
		FRuntimeFloatCurve OpenCurve;
	UPROPERTY(EditAnywhere)
		FRuntimeFloatCurve LocationCurve;
};

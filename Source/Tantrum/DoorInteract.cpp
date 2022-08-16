// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteract.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteract::UDoorInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteract::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	StartLocation = GetOwner()->GetActorLocation();
	FinalLocation = GetOwner()->GetActorLocation() + MovementVector;
	CurrentRotationTime = 0.0F;

	// ...
	
}


// Called every frame
void UDoorInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (CurrentRotationTime < TimeToRotate)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime/TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const float LocationAlpha = LocationCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FVector CurrentLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), FinalLocation, DeltaTime, TimeToRotate);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				//const FVector CurrentLocation = FMath::Lerp(StartLocation, FinalLocation, LocationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				GetOwner()->SetActorLocation(CurrentLocation);
			}
			else if (PlayerPawn && !TriggerBox->IsOverlappingActor(PlayerPawn) && ResetIfLeaveTrigger)
			{
				float distanceVal = FVector::Dist(GetOwner()->GetActorLocation(), StartLocation);
				UE_LOG(LogTemp, Warning, TEXT("dist val"), distanceVal);
				if (distanceVal >= 5)
				{
					const FVector CurrentLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), StartLocation, DeltaTime, TimeToReturn);
					GetOwner()->SetActorLocation(CurrentLocation);
				}
				//CurrentRotationTime -= DeltaTime;
				//const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				//const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				//const float LocationAlpha = LocationCurve.GetRichCurveConst()->Eval(TimeRatio);
				//const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				//const FVector CurrentLocation = FMath::Lerp(StartLocation, FinalLocation, LocationAlpha);
				//GetOwner()->SetActorRotation(CurrentRotation);
				//GetOwner()->SetActorLocation(CurrentLocation);
			}
		}
	}

	// ...
}


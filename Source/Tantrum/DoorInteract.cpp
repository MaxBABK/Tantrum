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
				if (!HasStarted)
				{
					UE_LOG(LogTemp, Warning, TEXT("Starting move %f, Time to rotate: %f"), CurrentRotationTime, TimeToRotate);
					
					HasStarted = true;
					StartRotation = GetOwner()->GetActorRotation();
					UE_LOG(LogTemp, Warning, TEXT("Start Rotation: %d, %d, %d"), StartRotation.Roll, StartRotation.Pitch, StartRotation.Yaw);
					StartLocation = GetOwner()->GetActorLocation();
					FinalLocation = GetOwner()->GetActorLocation() + MovementVector;
					FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;

				}
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime/TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				//const FVector CurrentLocation = FMath::Lerp(StartLocation, FinalLocation, LocationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				if (ChangeLocation)
				{
					const FVector CurrentLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), FinalLocation, DeltaTime, TimeToRotate);
					GetOwner()->SetActorLocation(CurrentLocation);

					//UE_LOG(LogTemp, Warning, TEXT("we are moving %f"), CurrentRotationTime);
				}
				
			}

		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("done done %f"), CurrentRotationTime);
	}

	if (ResetIfLeaveTrigger && ChangeLocation && HasStarted  )
	{
		float distanceVal = FVector::Dist(GetOwner()->GetActorLocation(), StartLocation);
		UE_LOG(LogTemp, Warning, TEXT("returning? %f"), distanceVal);
		if (distanceVal >= 5)
		{
			if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
			{
				APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
				if (PlayerPawn && !TriggerBox->IsOverlappingActor(PlayerPawn))
				{
					const FVector CurrentLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), StartLocation, DeltaTime, ReturnSpeed);
					GetOwner()->SetActorLocation(CurrentLocation);
					CurrentRotationTime -= DeltaTime;
				}
			}
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
	// ...
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"

#include "GameFramework/Actor.h"

// Sets default values
ADoorInteractionComponent::ADoorInteractionComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	FRotator DesiredRotation(0.0f, 90.0f, 0.0f);
	GetOwner()->SetActorRotation(DesiredRotation);
}

// Called every frame
void ADoorInteractionComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

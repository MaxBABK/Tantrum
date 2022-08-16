// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

#include "DoorInteract.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteract = CreateDefaultSubobject<UDoorInteract>(TEXT("DoorInteractComponent"));
}

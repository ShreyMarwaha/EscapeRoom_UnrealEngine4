// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "EscapeRoom.h"
#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"),*GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger volume
	//If the actor is in the trigger volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}


float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;
	//Find all the overlapping actors
	TArray<AActor*> OverlapptingActors;
	PressurePlate->GetOverlappingActors(OUT OverlapptingActors);
	// Iterate through them adding their masses
	for (const auto* Actor : OverlapptingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on pressure plate.\n"), *Actor->GetName());
	}

	return TotalMass;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ProximityTrigger.h"
#include "components/spherecomponent.h"

// Sets default values for this component's properties
UProximityTrigger::UProximityTrigger()
{
	SphereContact = CreateDefaultSubobject<USphereComponent>(TEXT("NPCProximityComponent"));
	SphereContact->SetSphereRadius(200.f, false);

	Activate();

	//GetOwner();
	//IsOwnerSelected();

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UProximityTrigger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProximityTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


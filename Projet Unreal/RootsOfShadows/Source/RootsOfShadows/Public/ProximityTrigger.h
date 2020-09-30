// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProximityTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOTSOFSHADOWS_API UProximityTrigger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProximityTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Sphere de contact */
	UPROPERTY(VisibleDefaultsOnly, Category = "NPCProximityTrigger")
		class USphereComponent* SphereContact;

		
};

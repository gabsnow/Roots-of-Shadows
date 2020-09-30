// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOTSOFSHADOWS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Attributes")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Attributes")
	float MaxHealth;

	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Perdre un montant de vie
	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	void LoseHealth(float healthToLose);
};

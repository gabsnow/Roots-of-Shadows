// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "RootsOfShadowsGameState.h"
#include "EnemyCharacter.h"
#include "RootsOfShadowsCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 31;
	Health = MaxHealth;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::LoseHealth(float healthToLose) {
	AActor* owner = GetOwner();
	AEnemyCharacter* enemyOwner = Cast<AEnemyCharacter>(owner);

	if (enemyOwner) {
		if (Health - healthToLose <= 0)
			Health = 0;
		else
			Health -= healthToLose;
		enemyOwner->OnHealthChanged();
	}		
	else {
		ARootsOfShadowsCharacter* charOwner = Cast<ARootsOfShadowsCharacter>(owner);
		if (charOwner) {			
			URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(charOwner->GetGameInstance());

			if (GameInstance->DatabasePlayer.Health - healthToLose <= 0) {
				GameInstance->DatabasePlayer.Health = 0;
				charOwner->Die();
			}				
			else
				GameInstance->DatabasePlayer.Health -= healthToLose;

			charOwner->OnHealthChanged();
		}
	}
}


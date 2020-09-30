// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CloseEnoughToAttack.generated.h"

/**
 * 
 */
UCLASS()
class ROOTSOFSHADOWS_API UCloseEnoughToAttack : public UBTService
{
	GENERATED_BODY()
		UCloseEnoughToAttack();
	/** Sera appelé à chaque «update» du service */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
		float DeltaSeconds) override;
};

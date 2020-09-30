
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SavingRessourcesBTService.generated.h"

UCLASS()
class ROOTSOFSHADOWS_API USavingRessourcesBTService : public UBTService
{
	GENERATED_BODY()

		USavingRessourcesBTService();
	/** Sera appelé à chaque «update» du service */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
		float DeltaSeconds) override;
};

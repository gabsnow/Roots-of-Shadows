
#include "SavingRessourcesBTService.h"
#include "AIControllercpp.h"

USavingRessourcesBTService::USavingRessourcesBTService()
{
	NodeName = "Checking if far enough of player to desactivate BT";
	Interval = 1;
	RandomDeviation = 0.1f;
}
void USavingRessourcesBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float
	DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	AIEnemyController->CheckIfTooFarFromSpawn();
}
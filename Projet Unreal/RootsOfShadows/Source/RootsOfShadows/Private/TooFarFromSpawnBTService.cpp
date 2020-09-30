
#include "TooFarFromSpawnBTService.h"
#include "AIControllercpp.h"

UTooFarFromSpawnBTService::UTooFarFromSpawnBTService()
{
	NodeName = "Checking if too far from spawn";
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}
void UTooFarFromSpawnBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float
	DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	AIEnemyController->CheckIfTooFarFromSpawn();
}
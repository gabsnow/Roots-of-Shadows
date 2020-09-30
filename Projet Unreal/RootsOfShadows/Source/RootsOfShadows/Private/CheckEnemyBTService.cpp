#include "CheckEnemyBTService.h"
#include "AIControllercpp.h"

UCheckEnemyBTService::UCheckEnemyBTService()
{
	NodeName = "CheckNearbyEnemy";
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}
void UCheckEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float
	DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	AIEnemyController->CheckNearbyEnemy();
}
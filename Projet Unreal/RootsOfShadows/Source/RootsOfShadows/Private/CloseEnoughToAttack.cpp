
#include "CloseEnoughToAttack.h"
#include "AIControllercpp.h"

UCloseEnoughToAttack::UCloseEnoughToAttack()
{
	NodeName = "CheckingIfCloseEnoughToAttack";
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}
void UCloseEnoughToAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float
	DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	AIEnemyController->CheckIfCloseEnough();
}
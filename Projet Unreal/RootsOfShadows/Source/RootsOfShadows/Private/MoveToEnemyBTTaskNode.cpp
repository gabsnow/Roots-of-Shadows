#include "MoveToEnemyBTTaskNode.h"
#include "AIControllercpp.h"
UMoveToEnemyBTTaskNode::UMoveToEnemyBTTaskNode()
{
	NodeName = "MoveToEnemy";
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveToEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8*NodeMemory)
{
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToEnemy();

	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		NodeResult = EBTNodeResult::Succeeded;
	}
	return NodeResult;
}
void UMoveToEnemyBTTaskNode::TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,float DeltaSeconds)
{
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToEnemy();

	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
FString UMoveToEnemyBTTaskNode::GetStaticDescription() const
{
	return TEXT("Poursuite du personnage principal");
}
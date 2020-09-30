// Fill out your copyright notice in the Description page of Project Settings.


#include "TooFarFromSpawnBTTaskNode.h"
#include "EnemyCharacter.h"
#include "AIControllercpp.h"
UTooFarFromSpawnBTTaskNode::UTooFarFromSpawnBTTaskNode()
{
	NodeName = "MoveToSpawn";
	bNotifyTick = true;
}
EBTNodeResult::Type UTooFarFromSpawnBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8*
	NodeMemory)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetOwner());
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToSpawnPoint();

	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("spawn succes"));
		AIEnemyController->IsGoingBackToSpawn = false;
		NodeResult = EBTNodeResult::Succeeded;
	}
	return NodeResult;

}
void UTooFarFromSpawnBTTaskNode::TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());

	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToSpawnPoint();
	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("spawn succes"));
		AIEnemyController->IsGoingBackToSpawn = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
FString UTooFarFromSpawnBTTaskNode::GetStaticDescription() const
{
	return TEXT("Retourne au spawn point");
}
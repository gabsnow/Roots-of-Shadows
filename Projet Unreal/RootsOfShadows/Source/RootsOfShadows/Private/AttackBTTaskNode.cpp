
#include "AttackBTTaskNode.h"
#include "EnemyCharacter.h"
#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "RootsOfShadowsCharacter.h"
#include "AIControllercpp.h"
#include "runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

UAttackBTTaskNode::UAttackBTTaskNode()
{
	NodeName = "AttackEnemy";
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	AIEnemyController->Attacking();
	//if(joueur mort, mob mort, mob trop loin du spawn(must turn back) condition pour que lattaque arrete(succeeded)) ou pt apres 1 attaque cest successful?
	NodeResult = EBTNodeResult::Succeeded;
	return NodeResult;
}
void UAttackBTTaskNode::TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ce message devrait pas apparaitre en theorie"));
	AAIControllercpp* AIEnemyController = Cast<AAIControllercpp>(OwnerComp.GetOwner());
	AIEnemyController->Attacking();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
FString UAttackBTTaskNode::GetStaticDescription() const
{
	return TEXT("Tente d'attaquer le hero");
}
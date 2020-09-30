#include "AIControllercpp.h"
#include "EngineUtils.h"
#include "runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "RootsOfShadowsCharacter.h"
#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"

void AAIControllercpp::CheckIfFarEnough()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool("CharacterFarEnough", true);
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetCharacter());
	ARootsOfShadowsCharacter* Player = Cast<ARootsOfShadowsCharacter>(GetCharacter());
	float distance = FVector::Distance(Enemy->CurrentPosition, Player->PlayerActualPosition);

	if (distance > DistanceToPlayerForDesactivation)
		BlackboardComponent->SetValueAsBool("CharacterFarEnough", NULL);
}

void AAIControllercpp::CheckNearbyEnemy()// merci Francois Jean
{
	if (!IsGoingBackToSpawn)
	{
		APawn* Pawn = GetPawn();
		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetCharacter());
		FVector MultiSphereStart = Pawn->GetActorLocation();
		FVector MultiSphereEnd = MultiSphereStart + FVector(0, 0, 15.0f);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(Pawn);
		ActorsToIgnore.Add(EnemyCharacter);
		TArray<FHitResult> OutHits;
		bool Result = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
			MultiSphereStart, // Point de départ de la ligne qui défini la multisphère
			MultiSphereEnd, // Fin de la ligne qui défini la multisphère
			RayonSphereAggro, // Rayon de la sphère
			ObjectTypes, // Types d'objets dont il faut tenir compte
			false, // false car nous n'utilisons pas le mode complexe
			ActorsToIgnore, // Acteurs à ignorer
			EDrawDebugTrace::None, // Le type de Debug
			OutHits, // Où seront stockés les résultats
			true); // true s'il faut ignorer l'objet lui-même
		UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject("TargetActorToFollow", NULL);
		ARootsOfShadowsCharacter* player = Cast<ARootsOfShadowsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (Result == true)
		{
			for (int32 i = 0; i < OutHits.Num(); i++)
			{
				FHitResult Hit = OutHits[i];

				ARootsOfShadowsCharacter* Character = Cast<ARootsOfShadowsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

				if (Hit.GetActor() == Character && !Character->IsDead)
					BlackboardComponent->SetValueAsObject("TargetActorToFollow", Character);
			}
		}
	}
}
void AAIControllercpp::CheckIfTooFarFromSpawn()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool("TooFar", NULL);
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetCharacter());
	CurrentDistanceFromSpawn = FVector::Distance(Enemy->InitialPosition, Enemy->CurrentPosition);
	if (CurrentDistanceFromSpawn >= Enemy->MaxDistanceFromSpawn)
	{
		IsGoingBackToSpawn = true;
		BlackboardComponent->SetValueAsBool("TooFar", true);
	}
	if (CurrentDistanceFromSpawn <= 500)
		IsGoingBackToSpawn = false;
}
void AAIControllercpp::CheckIfCloseEnough()
{

	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool("CloseEnoughToAttack", NULL);
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetCharacter());
	ARootsOfShadowsCharacter* Hero = Cast<ARootsOfShadowsCharacter>(BlackboardComponent->GetValueAsObject("TargetActorToFollow"));
	if (Hero != NULL && !Hero->IsDead)
	{
		Enemy->CurrentDistanceToHero = FVector::Distance(Enemy->CurrentPosition, Hero->GetActorLocation());

		if (Enemy->CurrentDistanceToHero <= Enemy->MaxDistanceToAttack + (Enemy->GetCapsuleComponent()->GetScaledCapsuleRadius() / 2))
		{
			BlackboardComponent->SetValueAsBool("CloseEnoughToAttack", true);
		}
	}
}
EPathFollowingRequestResult::Type AAIControllercpp::MoveToEnemy()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
	ARootsOfShadowsCharacter* HeroCharacterActor = Cast<ARootsOfShadowsCharacter>(
		BlackboardComponent->GetValueAsObject("TargetActorToFollow"));
	EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(Cast<AActor>(HeroCharacterActor), 1, false);
	if (HeroCharacterActor != NULL && !HeroCharacterActor->IsDead)
		SetFocus(HeroCharacterActor);
	else
	{
		IsGoingBackToSpawn = true;
		BlackboardComponent->SetValueAsBool("TooFar", true);
		MoveToSpawnPoint();
		SetFocus(NULL);
	}

	return MoveToActorResult;
}
EPathFollowingRequestResult::Type AAIControllercpp::MoveToSpawnPoint()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
	SetFocus(NULL);
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetCharacter());
	FVector Position;
	Position.X = Enemy->InitialPosition.X;
	Position.Y = Enemy->InitialPosition.Y;
	Position.Z = Enemy->CurrentPosition.Z;
	BlackboardComponent->SetValueAsBool("CloseEnoughToAttack", NULL);
	BlackboardComponent->SetValueAsObject("TargetActorToFollow", NULL);
	EPathFollowingRequestResult::Type MoveToActorResult = MoveToLocation(Position);
	if (Enemy->CurrentPosition == Position)
	{
		IsGoingBackToSpawn = false;
	}
	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		IsGoingBackToSpawn = false;
	}
	if (BlackboardComponent->GetValueAsBool("TargetActorToFollow") == NULL)
		Enemy->HealthComponent->Health = Enemy->HealthComponent->MaxHealth;
	return MoveToActorResult;
}
void AAIControllercpp::Attacking()
{
	UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
	ARootsOfShadowsCharacter* Hero = Cast<ARootsOfShadowsCharacter>(BlackboardComponent->GetValueAsObject("TargetActorToFollow"));
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetCharacter());
	SetFocus(Hero);

	if (Hero != NULL)
	{
		Enemy->AttackPlayer(Hero);
	}
}
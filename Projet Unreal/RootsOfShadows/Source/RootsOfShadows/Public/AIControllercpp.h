// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllercpp.generated.h"

/**
 * 
 */
UCLASS()
class ROOTSOFSHADOWS_API AAIControllercpp : public AAIController
{
	GENERATED_BODY()
public:
	// V�rifie si le joueur est asser loin pour pouvoir d�sactiver le behavior tree en vue de sauver des ressources
	UFUNCTION(BlueprintCallable, Category = "RessourcesSaving")
		void CheckIfFarEnough();

		/**
	* Nous v�rifions si le personnage est pr�s et si c'est le cas, nous pla�ons
	* une r�f�rence dans le BlackBoard. Cette fonction sera utilis�e par le service
	* CheckNearbyEnemyBTService du BT pour implanter la vigilance du NPC lorsque
	* nous approchons de sa zone de patrouille.
	*/
		UFUNCTION(BlueprintCallable, Category = "Aggro")
		void CheckNearbyEnemy();

		UFUNCTION(BlueprintCallable, Category = "Aggro")
			void CheckIfTooFarFromSpawn();

		UFUNCTION(BlueprintCallable, Category = "Aggro")
			void CheckIfCloseEnough();
		/**
* Fait en sorte que notre AIEnemyCharacter poursuive le joueur r�f�r� par la cl�
* TargetActorToFollow du Blackboard. Sera utilis�e dans une t�che du BT pour suivre le personnage
* principal (le joueur). En sortie, nous retournerons le r�sultat de MoveToActor (Failed,
* AlreadyAtGoal ou RequestSuccessful)
*/
		UFUNCTION(BlueprintCallable, Category = "Aggro")
			EPathFollowingRequestResult::Type MoveToEnemy();

		UFUNCTION(BlueprintCallable, Category = "Aggro")
			EPathFollowingRequestResult::Type MoveToSpawnPoint();

		UFUNCTION(BlueprintCallable, Category = "Aggro")
			void Attacking();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
			float CurrentDistanceFromSpawn = 0;	

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
			float RayonSphereAggro = 1200;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
			bool IsGoingBackToSpawn = false;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RessourcesSaving")
			bool FarEnoughFromPlayer = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RessourcesSaving")
			float DistanceToPlayerForDesactivation = 10000; // pour les tests(si jamais joublie de la remettre a une valeur logique genre 10 000)
};

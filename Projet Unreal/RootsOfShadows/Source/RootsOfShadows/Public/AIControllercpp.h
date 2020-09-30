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
	// Vérifie si le joueur est asser loin pour pouvoir désactiver le behavior tree en vue de sauver des ressources
	UFUNCTION(BlueprintCallable, Category = "RessourcesSaving")
		void CheckIfFarEnough();

		/**
	* Nous vérifions si le personnage est près et si c'est le cas, nous plaçons
	* une référence dans le BlackBoard. Cette fonction sera utilisée par le service
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
* Fait en sorte que notre AIEnemyCharacter poursuive le joueur référé par la clé
* TargetActorToFollow du Blackboard. Sera utilisée dans une tâche du BT pour suivre le personnage
* principal (le joueur). En sortie, nous retournerons le résultat de MoveToActor (Failed,
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

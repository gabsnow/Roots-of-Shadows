// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "NPCCharacter.h"
#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "RootsOfShadowsCharacter.generated.h"

UCLASS(config=Game)
class ARootsOfShadowsCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	void VainquishEnemy(AEnemyCharacter* Enemy);

	void GainExp(float Exp);

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Is camera moveable ?
	bool isCameraMoveable{ false };

	// mouse position
	float mouseX;
	float mouseY;

	//ranges des attaques
	const int rangeAttack1 = 350;
	const int rangeAttack2 = 350;
	const int rangeMagicAttack = 1500;

	
public:
	ARootsOfShadowsCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Position")
		FVector PlayerActualPosition;

	////////////////////////////// Anim
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimationAsset* AnimAttack1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimationAsset* AnimAttack2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimationAsset* AnimMagicAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimationAsset* AnimDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	FTimerHandle FinishAttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	FTimerHandle SwitchAttackTimer;

	//quand on level up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
	UParticleSystemComponent* LevelUpParticles;

	UFUNCTION(BlueprintCallable, Category = "Particle")
	void ActivatePPLevelUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quests")
	bool bQuestUIIsOpen;

	bool WeGotTooFar();

	UFUNCTION(BlueprintImplementableEvent, Category = "Quests")
	void WeGotTooFarFromNPC();


	// Remettre le animation mode au blueprint
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void SetAnimBP();

	// Remettre le animation mode au blueprint
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void KeepAttacking();

	UFUNCTION(BlueprintCallable, Category = "Regeneration")
	void Regeneration();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Regeneration")
	float ElapsedTime;

	/*-----------------------------------*/
	//delais des attaques
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	int A1TimerCooldownTime = 2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	int A2TimerCooldownTime = 8;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	int MagicTimerCooldownTime = 12;

	//fonction pour les events delais des attaques
	UFUNCTION(BlueprintImplementableEvent, Category = "Cooldown")
	void OnSpecialAttackCast();
	UFUNCTION(BlueprintImplementableEvent, Category = "Cooldown")
	void OnMagicAttackCast();
	UFUNCTION(BlueprintImplementableEvent, Category = "Cooldown")
	void OnSpecialAttackCooledDown();
	UFUNCTION(BlueprintImplementableEvent, Category = "Cooldown")
	void OnMagicAttackCooledDown();
	/*-----------------------------------*/

	// The player has moved since last normal attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player attributes")
	bool hasMoved;

	// Position of last normal attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player attributes")
	FVector LastPos;

	/////////////////////////////////////

	// Selected character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	class ACharacter* Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	class UHealthComponent* HealthComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	///** The amont of experience the player has */
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	//float XP;

	///** The amount of mana the player has */
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	//float Mana;

	// Mana used by magic attack
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player attributes")
	float MagicAttackManaUse;

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void Respawn();

	// Si le joueur est mort
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player attributes")
	bool IsDead;

	// Attaque déclenchée par la touche 1
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void DoAttack1();

	// Attaque déclenchée par la touche 2
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void DoAttack2();

	// Attaque déclenchée par la touche 3
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void DoMagicAttack();

	/** Touche 1 Activée */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attacking")
	bool bPressed1;

	//On active le booléen bPressed1 et attaque
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void OnPressAttack1();

	//On désactive le booléen bPressed1
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void OnReleaseAttack1();

	/** Touche 2 Activée */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attacking")
	bool bPressed2;

	//On active le booléen bPressed2 et attaque
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void OnPressAttack2();

	//On désactive le booléen bPressed2
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void OnReleaseAttack2();

	/** Touche 2 Activée */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attacking")
	bool bPressed3;

	//On active le booléen bPressed3 et attaque
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void OnPressMagicAttack();

	//On désactive le booléen bPressed3
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void OnReleaseMagicAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attacking")
	bool ennemyIsInRangeOfAttack;

	/////////////////////////////////////////////////////////////
	// Is the attack1 timer expired
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	bool bAttack1TimerExpired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FTimerHandle Attack1TimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void UnsetTimerAttack1();

	// Is the attack2 timer expired
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	bool bAttack2TimerExpired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FTimerHandle Attack2TimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void UnsetTimerAttack2();

	// Is the MagicAttack timer expired
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	bool bMagicAttackTimerExpired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FTimerHandle MagicAttackTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void UnsetTimerMagicAttack();

	UFUNCTION(BlueprintCallable, Category = "Enemy Attributes")
	void setEnnemyInRange(int attaque/*1 2 ou 3*/);
	////////////////////////////////////////////////////////////////////////

	// Event quand on change de sélection
	UFUNCTION(BlueprintImplementableEvent, Category = "Selection")
	void OnSelectedNpcChanged();

	//Custom event de quand on perd de la vie
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnManaChanged();

	//Custom event de quand on perd de la vie
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnHealthChanged();

	//Custom event de quand on perd de la vie
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnExpChanged();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnDie();

	FVector posWhenSpeakWNPC;
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Turn(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	void LookUp(float Value);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// Activer les mouvements de caméra
	void CameraMovementStart();

	// Désactiver les mouvements de caméra
	void CameraMovementStop();

	// Permet de sélectionner un NPC si l'on a cliqué sur un
	void Select();

	// Permet d'interragir avec un NPC si l'on a cliqué sur un 
	void Interact();

	// on se met face a un ennemi quand on l'attaque
	FRotator GetRotationFacingEnnnemy(AEnemyCharacter* enemyTarget);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma region Quest

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	bool isLastDialog{ false };

	int nbDialog{0};

	int questIndex{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	int questNpcId{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	class ANPCCharacter* selectedNpc;

	UFUNCTION(BlueprintCallable, Category = Quest)
	void setQuestIndex(int index);

	UFUNCTION(BlueprintCallable, Category = Quest)
	void setQuestIndexOneUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
	bool npcTalkableDistance{ false };

	UFUNCTION(BlueprintCallable)
	void AcceptQuest();

	UFUNCTION(BlueprintCallable)
	void CompleteQuest();

	UFUNCTION(BlueprintCallable)
	void SetQuestProgress();

	UFUNCTION(BlueprintCallable)
	void TurnQuest();

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestComplete();

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestProgress();
#pragma endregion
};
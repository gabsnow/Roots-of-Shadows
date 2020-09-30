// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ROOTSOFSHADOWS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	#pragma region Attributes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Attributes")
	int32 ID;

	//// Remettre le animation mode au blueprint
	//UFUNCTION(BlueprintCallable, Category = "Attacking")
	//	void SetAnimBP();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	//	UAnimationAsset* AnimAsset;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	//	FString AnimAssetReference;

	// pour les animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animations")
	bool bIsCurrentlyFighting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animations")
	bool bIsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animations")
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animations")
	bool bIsCurrentlyRoaming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animations")
	bool bIsIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Attributes")
	float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Attributes")
	float ExpGain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Attributes")
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	bool bIsSelected;
	
	// Is the respawn timer expired
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	bool bTimerExpired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FTimerHandle RespawnTimerHandle;

	//// activate timer for respawn
	//UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	//void ActivateTimer();

	// Faire mourrir l'ennemi
	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	void Die();

	// Faire réapparaitre un ennemi 
	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	void Respawn();

	//fix respawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FVector InitialPosition;

	//fix respawn
	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	FVector GetANewLocaltion();

	//fix respawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	bool canAttack;

	//Custom event de quand on perd de la vie
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Event")
	void OnHealthChanged();

	//quand on perd de la vie on retourne le pourcentage de vie
	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	int GetHealthBarPercentage();

	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	void AttackPlayer(ARootsOfShadowsCharacter* Hero);

	//quand on perd de la vie on retourne une couleur
	UFUNCTION(BlueprintCallable, Category = "Enemy Functions")
	FVector GetHealthBarColor();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
	FVector CurrentPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
	float CurrentDistanceFromSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
	float CurrentDistanceToHero = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
	int MaxDistanceFromSpawn = 4000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro")
	int MaxDistanceToAttack = 350;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animation")
	UAnimationAsset* AnimAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animation")
	UAnimationAsset* AnimDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Animation")
	float delaisPerteDeVie = 2.0f;

	//DeathAnimationTimer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FTimerHandle DeathAnimTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Attributes")
	FTimerHandle AttackTimerHandle;

	//Pour l'attaque magique
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
	UParticleSystemComponent* ParticleSystem;
	#pragma endregion	
	
	class ARootsOfShadowsCharacter* HeroToAttack;

	bool AttackOnGoing{ false };

	void Attack();

	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "RootsOfShadowsGameState.h"
#include "Kismet/GameplayStatics.h"

#include "HealthComponent.h"
#include "Components/ActorComponent.h"
#include <time.h>
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include <stdlib.h>     // srand, rand 
#include <time.h>	    // time for random
#include "RootsOfShadowsCharacter.h"
#include "AIControllercpp.h"
#include "BrainComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Engine/EngineTypes.h"
#include "Animation/AnimSequence.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimBlueprintGeneratedClass.h"

//#include "Components/WidgetComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Emitter"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemFinder(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/Impact/P_Impact_Enemy_Fire_Strong.P_Impact_Enemy_Fire_Strong'"));

	if (ParticleSystemFinder.Succeeded())
		ParticleSystem->Template = ParticleSystemFinder.Object;

	ParticleSystem->AttachTo(RootComponent);

	canAttack = true;

	//initialize random
	srand(time(NULL));

	//static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimAttack(AnimAssetReference);
	//AnimAsset = AnimAttack.Object;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = this->GetActorLocation();
	GetCharacterMovement()->MaxWalkSpeed = 400;

	ParticleSystem->DeactivateSystem();
}

//void AEnemyCharacter::BeginDestroy() {
//	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AEnemyCharacter::Respawn, 2);
//	Super::BeginDestroy();
//}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentPosition = GetActorLocation();
	FVector movement = this->GetMovementComponent()->Velocity;

	if((movement.X != 0 || movement.Y != 0 || movement.Z != 0) && GetMesh()->GetAnimationMode() != EAnimationMode::Type::AnimationBlueprint)
		GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::Die() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Die()")));
	//this->SetActorHiddenInGame(true);
	AttackOnGoing = false;
	bIsSelected = false;
	bIsDead = true;
	this->GetController()->StopMovement();
	GetMesh()->PlayAnimation(AnimDeath, false);
	auto a = Cast<AAIControllercpp>(GetController());// ->GetBrainComponent()->StopLogic();
	a->GetBrainComponent()->StopLogic("Dead");
	a->SetFocus(NULL);
	
	SetActorEnableCollision(false);

	GetWorldTimerManager().ClearTimer(DeathAnimTimer);
	GetWorldTimerManager().SetTimer(DeathAnimTimer, this, &AEnemyCharacter::Respawn, 10);

	//URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());
	//FDBPlayer dbp = GameInstance->DatabasePlayer;

	//dbp.Experience += ExpGain;

	//if (dbp.Experience >= dbp.NextLevelExp) {
	//	dbp.PreviousLevelExp = dbp.NextLevelExp;
	//	dbp.NextLevelExp *= 2;
	//}

	//GameInstance->UpdatePlayer();

	//ARootsOfShadowsCharacter* PlayerChar = Cast<ARootsOfShadowsCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//PlayerChar->OnExpChanged();

	//Respawn();
	//Destroy();

	// Get the current location  
	//FVector NewLocation = this->GetActorLocation();
	// Move it slightly  
	//NewLocation.Z += 2000.0f;
	// Set the location- this will blindly place the actor at the given location  
	//this->SetActorLocation(InitialPosition, true, nullptr, ETeleportType::TeleportPhysics);

	//canAttack = false;
	//ActivateTimer();
}

void AEnemyCharacter::Respawn()
{
	//GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
	FVector pos = InitialPosition;
	// Spawn another like us at initial position
	GetWorld()->SpawnActor<AEnemyCharacter>(GetClass(), pos, FRotator::ZeroRotator);

	//// Set the location- this will blindly place the actor at the given location  
	//this->SetActorLocation(GetANewLocaltion(), true, nullptr, ETeleportType::TeleportPhysics);

	//this->HealthComponent->Health = this->HealthComponent->MaxHealth;
	//this->SetActorHiddenInGame(false);
	//canAttack = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Respawn done.")));

	Destroy();
}

//void AEnemyCharacter::ActivateTimer()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("ActivateTimer()")));
//
//	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AEnemyCharacter::Respawn, 30);	
//}

FVector AEnemyCharacter::GetANewLocaltion() {


	FVector newLocation = InitialPosition;//juste pour pas qu'elle soit a 0

	newLocation.X = (rand() % 400 + 1) + (InitialPosition.X - 200);
	newLocation.Y = (rand() % 400 + 1) + (InitialPosition.Y - 200);
	newLocation.Z = InitialPosition.Z + 1000;// on le met plus haut pour qu'il reste pas coincé dans une montagne par exemple

	return newLocation;

}

int AEnemyCharacter::GetHealthBarPercentage() {
	float notreVie = HealthComponent->Health;
	float maxVita = HealthComponent->MaxHealth;
	return (100.0f * notreVie) / maxVita;
}

FVector AEnemyCharacter::GetHealthBarColor() {
	float notreVie = HealthComponent->Health;
	float maxVita = HealthComponent->MaxHealth;

	float viePourcentage = (100.0f * notreVie) / maxVita;

	FVector vecteurCouleur;

	//on set le vert
	vecteurCouleur.Y = (255.0f * viePourcentage) / maxVita;

	//on set le rouge
	vecteurCouleur.X =  255.0f - ((255.0f * viePourcentage) / maxVita);

	//on a pas de bleu
	vecteurCouleur.Z = 0.0f;

	return vecteurCouleur;
}

void AEnemyCharacter::AttackPlayer(ARootsOfShadowsCharacter* Hero)
{
	if (!AttackOnGoing) {
		AttackOnGoing = true;
		HeroToAttack = Hero;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Play anim attack player")));
		GetMesh()->PlayAnimation(AnimAttack, false);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::Attack, delaisPerteDeVie);
	}
}

void AEnemyCharacter::Attack() {
	HeroToAttack->HealthComponent->LoseHealth(AttackPower*3);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Set anim bp for enemy")));

	if (HealthComponent->Health > 0)
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	AttackOnGoing = false;
}

//void AEnemyCharacter::SetAnimBP()
//{
//	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
//}
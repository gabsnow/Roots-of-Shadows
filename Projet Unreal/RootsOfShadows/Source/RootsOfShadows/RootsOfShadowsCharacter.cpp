// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RootsOfShadowsCharacter.h"

#include "RootsOfShadowsGameState.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "UnrealClient.h"

#include "Public/NPCCharacter.h"

#include <string>
#include "TimerManager.h"

#include "Engine/EngineTypes.h"


#include "Animation/AnimSequence.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "GameFramework/Character.h"
#include "Animation/AnimBlueprintGeneratedClass.h"

#pragma region Defaults

//////////////////////////////////////////////////////////////////////////
// ARootsOfShadowsCharacter

ARootsOfShadowsCharacter::ARootsOfShadowsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//Autorise les Overlap events (lorsqu'on entre dans une zone)
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create the health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	
	bAttack1TimerExpired = true;
	bAttack2TimerExpired = true;
	bMagicAttackTimerExpired = true;
	MagicAttackManaUse = 50;

	//set current selected npc to no one bitch
	selectedNpc = NULL;
	ennemyIsInRangeOfAttack = false;

	hasMoved = true;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimAttack1Finder(TEXT("AnimSequence'/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Ability_E.Ability_E'"));
	AnimAttack1 = AnimAttack1Finder.Object;

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimAttack2Finder(TEXT("AnimSequence'/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Ability_R.Ability_R'"));
	AnimAttack2 = AnimAttack2Finder.Object;

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimAnimMagicAttackFinder(TEXT("AnimSequence'/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Cast.Cast'"));
	AnimMagicAttack = AnimAnimMagicAttackFinder.Object;

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimDeathFinder(TEXT("AnimSequence'/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Death.Death'"));
	AnimDeath = AnimDeathFinder.Object;

	//init le particle system de level up
	LevelUpParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Emitter"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemFinder(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Cines/Ausar/P_Ausar_Resurrection.P_Ausar_Resurrection'"));

	if (ParticleSystemFinder.Succeeded())
		LevelUpParticles->Template = ParticleSystemFinder.Object;

	LevelUpParticles->AttachTo(RootComponent);
}

void ARootsOfShadowsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("EnableCameraMovement", IE_Pressed, this, &ARootsOfShadowsCharacter::CameraMovementStart);
	PlayerInputComponent->BindAction("EnableCameraMovement", IE_Released, this, &ARootsOfShadowsCharacter::CameraMovementStop);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARootsOfShadowsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARootsOfShadowsCharacter::MoveRight);

	// Attack1
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &ARootsOfShadowsCharacter::OnPressAttack1);
	PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ARootsOfShadowsCharacter::OnReleaseAttack1);

	// Attack2
	PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &ARootsOfShadowsCharacter::OnPressAttack2);
	PlayerInputComponent->BindAction("Attack2", IE_Released, this, &ARootsOfShadowsCharacter::OnReleaseAttack2);

	// MagicAttack
	PlayerInputComponent->BindAction("MagicAttack", IE_Pressed, this, &ARootsOfShadowsCharacter::OnPressMagicAttack);
	PlayerInputComponent->BindAction("MagicAttack", IE_Released, this, &ARootsOfShadowsCharacter::OnReleaseMagicAttack);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ARootsOfShadowsCharacter::Turn);
	//PlayerInputComponent->BindAxis("TurnRate", this, &ARootsOfShadowsCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ARootsOfShadowsCharacter::LookUp);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &ARootsOfShadowsCharacter::LookUpAtRate);

	// handle touch devices
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &ARootsOfShadowsCharacter::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &ARootsOfShadowsCharacter::TouchStopped);

	// VR headset functionality
	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ARootsOfShadowsCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &ARootsOfShadowsCharacter::Select);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARootsOfShadowsCharacter::Interact);
	//PlayerInputComponent->BindAction("Select", IE_Released, this, &ARootsOfShadowsCharacter::SelectStop);
}

void ARootsOfShadowsCharacter::BeginPlay(){
	Super::BeginPlay();
	IsDead = HealthComponent->Health <= 0;
	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (playerController) {
		playerController->bShowMouseCursor = true;
		playerController->bEnableClickEvents = true;
		playerController->bEnableMouseOverEvents = true;
	}

	bQuestUIIsOpen = false;

	//on désactive le system apres l'initialisation du monde pour l'activer quand on level up
	LevelUpParticles->DeactivateSystem();
}
void ARootsOfShadowsCharacter::Regeneration()
{
	if (!IsDead)
	{
		URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(this->GetGameInstance());

		// Regeneration de la mana de 5%
		if (GameInstance->DatabasePlayer.Mana + (GameInstance->DatabasePlayer.MaxMana / 20) > GameInstance->DatabasePlayer.MaxMana)
			GameInstance->DatabasePlayer.Mana = GameInstance->DatabasePlayer.MaxMana;
		else
			GameInstance->DatabasePlayer.Mana += (GameInstance->DatabasePlayer.MaxMana / 20);

		// Regeneration de la vie de 5%
		if (GameInstance->DatabasePlayer.Health + (GameInstance->DatabasePlayer.MaxHealth / 20) > GameInstance->DatabasePlayer.MaxHealth)
			GameInstance->DatabasePlayer.Health = GameInstance->DatabasePlayer.MaxHealth;
		else
			GameInstance->DatabasePlayer.Health += (GameInstance->DatabasePlayer.MaxHealth / 20);
		this->OnManaChanged();
		this->OnHealthChanged();
	}
}
void ARootsOfShadowsCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}
void ARootsOfShadowsCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ARootsOfShadowsCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ARootsOfShadowsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (isCameraMoveable)
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARootsOfShadowsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (isCameraMoveable)
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARootsOfShadowsCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !IsDead)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		// On remet le Anim BP
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

		if (bQuestUIIsOpen) {
			if (WeGotTooFar()) {
				WeGotTooFarFromNPC();
			}
		}
	}
}

void ARootsOfShadowsCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !IsDead)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);

		// On remet le anim mode
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

		if (bQuestUIIsOpen){
			if (WeGotTooFar()) {
				WeGotTooFarFromNPC();
			}
		}
			

	}
}

bool ARootsOfShadowsCharacter::WeGotTooFar() {

	float distance = (posWhenSpeakWNPC - this->GetActorLocation()).Size();

	return (distance > 350) ? true : false;

}

void ARootsOfShadowsCharacter::Turn(float Value) {
	if (isCameraMoveable) {
		APlayerController* playerController = Cast<APlayerController>(GetController());

		if (playerController) {
			AddControllerYawInput(Value);

			FViewport* v = CastChecked<ULocalPlayer>(playerController->Player)->ViewportClient->Viewport;
			v->SetMouse(mouseX, mouseY);
		}		
	}
}

void ARootsOfShadowsCharacter::LookUp(float Value) {
	if (isCameraMoveable) {
		APlayerController* playerController = Cast<APlayerController>(GetController());

		if (playerController) {
			AddControllerPitchInput(Value);

			FViewport* v = CastChecked<ULocalPlayer>(playerController->Player)->ViewportClient->Viewport;
			v->SetMouse(mouseX, mouseY);
		}
	}
}

#pragma endregion

void ARootsOfShadowsCharacter::VainquishEnemy(AEnemyCharacter* Enemy) {
	Enemy->Die();
	Target = nullptr;

	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());
	FDBTaskProgress tp = GameInstance->DatabaseTaskProgress;

	if (tp.EnemyId == Enemy->ID) {
		if (GameInstance->DatabaseTaskProgress.QuantityLeft > 0) {
			int32 QuestId = -1;

			for (int i(0); i < GameInstance->DatabaseQuestTasks.Num(); i++)
				if (GameInstance->DatabaseQuestTasks[i].QuestTaskId == tp.QuestTaskId)
					QuestId = GameInstance->DatabaseQuestTasks[i].QuestId;


			GameInstance->DatabaseTaskProgress.QuantityLeft--;
			GameInstance->SetQuestProgress(QuestId, GameInstance->DatabaseTaskProgress.QuantityLeft);
			OnQuestProgress();
			if (GameInstance->DatabaseTaskProgress.QuantityLeft == 0)
				CompleteQuest();
		}			
	}
		

	GainExp(Enemy->ExpGain);
}

void ARootsOfShadowsCharacter::GainExp(float Exp) {
	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());
	GameInstance->DatabasePlayer.Experience += Exp;;
	GameInstance->DatabasePlayer.Position = GetActorLocation();

	if (GameInstance->DatabasePlayer.Experience >= GameInstance->DatabasePlayer.NextLevelExp) {
		GameInstance->DatabasePlayer.PreviousLevelExp = GameInstance->DatabasePlayer.NextLevelExp;
		GameInstance->DatabasePlayer.NextLevelExp *= 2;
		GameInstance->DatabasePlayer.Level += 1;

		// Gain de compétences assez plate mais...bon, sinon on fera un switch(case) avec le niveau mais
		// déja la on gagne de plus en plus!
		const float maxHpGain = 25, maxMpGain = 10, strGain = 2.5, intGain = 2.5;

		GameInstance->DatabasePlayer.MaxHealth += (GameInstance->DatabasePlayer.Level * maxHpGain);
		GameInstance->DatabasePlayer.MaxMana += (GameInstance->DatabasePlayer.Level * maxMpGain);
		GameInstance->DatabasePlayer.Strength += (GameInstance->DatabasePlayer.Level * strGain);
		GameInstance->DatabasePlayer.Intelligence += (GameInstance->DatabasePlayer.Level * intGain);

		// On level up alors on full la health et la mana
		GameInstance->DatabasePlayer.Health = GameInstance->DatabasePlayer.MaxHealth;
		GameInstance->DatabasePlayer.Mana = GameInstance->DatabasePlayer.MaxMana;

		this->OnHealthChanged();
		this->OnManaChanged();

		//ensuite on déclence l'animation de particules de level up
		ActivatePPLevelUp();
	}
	GameInstance->UpdatePlayer();

	this->OnExpChanged();
}

void ARootsOfShadowsCharacter::CameraMovementStart() {	
	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (playerController) {
		playerController->GetMousePosition(mouseX, mouseY);
		isCameraMoveable = true;
		playerController->bShowMouseCursor = false;
	}
}

void ARootsOfShadowsCharacter::CameraMovementStop() {
	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (playerController) {
		isCameraMoveable = false;
		playerController->bShowMouseCursor = true;
	}	
}

void ARootsOfShadowsCharacter::Select() {
	if (GetWorld() != NULL) {
		// On commence par déselectionner notre selection si on en a une
		if (Target) {
			AEnemyCharacter* enemyTarget = Cast<AEnemyCharacter>(Target);

			if (enemyTarget)
				enemyTarget->bIsSelected = false;
			else {
				ANPCCharacter* npcTarget = Cast<ANPCCharacter>(Target);

				if (npcTarget)
					npcTarget->bIsSelected = false;
			}
		}

		// Ensuite on passe à vérifier la nouvelle sélection
		APlayerController* controller = GetWorld()->GetFirstPlayerController();		
		FHitResult hitActor;
		
		controller->GetHitResultUnderCursor(ECC_Pawn, false, hitActor);

		if (hitActor.bBlockingHit && hitActor.Actor != NULL) {			
			Target = Cast<ACharacter>(hitActor.GetActor());

			ACharacter* ourself = controller->GetCharacter();

			// on est sur qu'on ne s'est pas target nous même					
			if (ourself && Target != ourself) {				
				// est-ce qu'on a target un ennemi ?				
				AEnemyCharacter* enemyTarget = Cast<AEnemyCharacter>(Target);

				if (enemyTarget && !enemyTarget->bIsDead) {
					enemyTarget->bIsSelected = true;
				}
				else {
					ANPCCharacter* npcTarget = Cast<ANPCCharacter>(Target);

					if (npcTarget) {
						npcTarget->bIsSelected = true;
						posWhenSpeakWNPC = this->GetActorLocation();

						if (Target) {						
							FVector NpcPos = npcTarget->GetActorLocation();
							FVector PlayerPos = this->GetActorLocation();
							float distance = (PlayerPos - NpcPos).Size();
							if (distance <= 350) {
								selectedNpc = npcTarget;
								npcTalkableDistance = true;
								OnSelectedNpcChanged();
							}
							else {
								selectedNpc = NULL;
								npcTalkableDistance = true;
							}								
						}													
					}
					else
						Target = nullptr;
				}								
			}
			else
				Target = nullptr;
		}
		else
			Target = nullptr;
	}	
}

void ARootsOfShadowsCharacter::Interact() {

}

void ARootsOfShadowsCharacter::DoAttack1()
{
	if (hasMoved)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("hasMoved is true so set it false and start timer")));
		hasMoved = false;
		GetWorldTimerManager().SetTimer(Attack1TimerHandle, this, &ARootsOfShadowsCharacter::DoAttack1, A1TimerCooldownTime);

	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("hasMoved is false")));
		GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
		GetWorldTimerManager().ClearTimer(Attack1TimerHandle);

		if (LastPos != GetActorLocation())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("LastPos != actor location")));
			SetAnimBP();
			hasMoved = true;
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("LastPos == actor location")));
			GetWorldTimerManager().SetTimer(Attack1TimerHandle, this, &ARootsOfShadowsCharacter::DoAttack1, 2);
		}

	}

	if (!hasMoved)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Attaque1()")));
		if (Target) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Target = true")));
			FVector EnemyPos = Target->GetActorLocation();
			FVector PlayerPos = this->GetActorLocation();
			float distance = (PlayerPos - EnemyPos).Size();
			FString distString = FString::SanitizeFloat(distance);

			// HitBox
			float radius = Target->GetCapsuleComponent()->GetScaledCapsuleRadius();			

			if (distance <= 350 + (radius / 2))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("distance <= 300")));
				AEnemyCharacter* enemyTarget = Cast<AEnemyCharacter>(Target);

				if (enemyTarget)
				{
					URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(this->GetGameInstance());
					GetMesh()->PlayAnimation(AnimAttack1, false);
					enemyTarget->HealthComponent->LoseHealth(GameInstance->DatabasePlayer.Strength);
					GetWorldTimerManager().SetTimer(FinishAttackTimer, this, &ARootsOfShadowsCharacter::SetAnimBP, 2.4f);


					this->SetActorRotation(GetRotationFacingEnnnemy(enemyTarget));

					if (enemyTarget->HealthComponent->Health <= 0)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Die()")));
						VainquishEnemy(enemyTarget);
						hasMoved = true;
						GetWorldTimerManager().ClearTimer(Attack1TimerHandle);
					}
				}
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Magenta, "You are " + distString + "m away from the selected character");
			}
		}
	}
}

void ARootsOfShadowsCharacter::SetAnimBP()
{
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
	GetWorldTimerManager().ClearTimer(FinishAttackTimer);
}

void ARootsOfShadowsCharacter::KeepAttacking()
{
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
	GetWorldTimerManager().ClearTimer(FinishAttackTimer);

	if (Target != nullptr && GetWorldTimerManager().GetTimerRemaining(SwitchAttackTimer) == -1)
	{
		this->OnPressAttack1();
	}
}

void ARootsOfShadowsCharacter::DoAttack2()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Attaque2()")));
	if (Target) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Target = true")));
		FVector EnemyPos = Target->GetActorLocation();
		FVector PlayerPos = this->GetActorLocation();
		float distance = (PlayerPos - EnemyPos).Size();
		FString distString = FString::SanitizeFloat(distance);

		// HitBox
		float radius = Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

		if (distance <= 350 + (radius / 2))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("distance <= 300")));
			AEnemyCharacter* enemyTarget = Cast<AEnemyCharacter>(Target);

			if (enemyTarget)
			{
				OnSpecialAttackCast();
				URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(this->GetGameInstance());
				GetMesh()->PlayAnimation(AnimAttack2, false);
				enemyTarget->HealthComponent->LoseHealth(GameInstance->DatabasePlayer.Strength * 1.5f);

				GetWorldTimerManager().SetTimer(FinishAttackTimer, this, &ARootsOfShadowsCharacter::KeepAttacking, 2.0f);
				GetWorldTimerManager().SetTimer(Attack2TimerHandle, this, &ARootsOfShadowsCharacter::UnsetTimerAttack2, A2TimerCooldownTime);
				bAttack2TimerExpired = false;

				this->SetActorRotation(GetRotationFacingEnnnemy(enemyTarget));

				if (enemyTarget->HealthComponent->Health <= 0)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Die()")));
					VainquishEnemy(enemyTarget);
				}
			}
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Magenta, "You are " + distString + "m away from the selected character");
		}
	}
}

void ARootsOfShadowsCharacter::DoMagicAttack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("DoMagicAttack()")));
	if (Target) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Target = true")));
		FVector EnemyPos = Target->GetActorLocation();
		FVector PlayerPos = this->GetActorLocation();
		float distance = (PlayerPos - EnemyPos).Size();
		FString distString = FString::SanitizeFloat(distance);
		URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(this->GetGameInstance());

		if (GameInstance->DatabasePlayer.Mana >= MagicAttackManaUse)
		{
			// HitBox
			float radius = Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

			if (distance <= 1500 + (radius / 2))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("distance <= 1500")));
				AEnemyCharacter* enemyTarget = Cast<AEnemyCharacter>(Target);

				if (enemyTarget)
				{
					OnMagicAttackCast();
					GetMesh()->PlayAnimation(AnimMagicAttack, false);
					enemyTarget->HealthComponent->LoseHealth(GameInstance->DatabasePlayer.Strength + (GameInstance->DatabasePlayer.Intelligence * 1.5f));
					enemyTarget->ParticleSystem->ActivateSystem();

					// Mana //////////////////////////////////////////////////////////////////////////////////////////////
					if (GameInstance->DatabasePlayer.Mana - MagicAttackManaUse <= 0) {
						GameInstance->DatabasePlayer.Mana = 0;
					}
					else
						GameInstance->DatabasePlayer.Mana -= MagicAttackManaUse;

					this->OnManaChanged();
					///////////////////////////////////////////////////////////////////////////////////////////////////////

					GetWorldTimerManager().SetTimer(FinishAttackTimer, this, &ARootsOfShadowsCharacter::KeepAttacking, 0.967f);
					GetWorldTimerManager().SetTimer(MagicAttackTimerHandle, this, &ARootsOfShadowsCharacter::UnsetTimerMagicAttack, MagicTimerCooldownTime);
					bMagicAttackTimerExpired = false;

					this->SetActorRotation(GetRotationFacingEnnnemy(enemyTarget));

					if (enemyTarget->HealthComponent->Health <= 0)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Die()")));
						VainquishEnemy(enemyTarget);
					}
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Magenta, "You are " + distString + "m away from the selected character");
			}
		}
		else
			OnPressAttack1();
	}
}

void ARootsOfShadowsCharacter::OnPressAttack1()
{
	bPressed1 = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("OnPressAttack1()")));

	if (GetWorldTimerManager().GetTimerRemaining(Attack1TimerHandle) == -1 && GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer) == -1)
	{
		LastPos = GetActorLocation();
		this->DoAttack1();
	}
	else/* if (GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer) < 3.0f)*/
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Switching Attack")));
		float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer)/* + 0.1f*/;

		GetWorldTimerManager().SetTimer(SwitchAttackTimer, this, &ARootsOfShadowsCharacter::OnPressAttack1, TimeRemaining);
	}
}

void ARootsOfShadowsCharacter::OnReleaseAttack1()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("OnReleaseAttack1()")));
	bPressed1 = false;
}

void ARootsOfShadowsCharacter::OnPressAttack2()
{
	GetWorldTimerManager().ClearTimer(SwitchAttackTimer);

	bPressed2 = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("OnPressAttack2()")));

	if (GetWorldTimerManager().GetTimerElapsed(Attack2TimerHandle) == -1 && GetWorldTimerManager().GetTimerElapsed(FinishAttackTimer) == -1)
		this->DoAttack2();
	else if (GetWorldTimerManager().GetTimerRemaining(Attack2TimerHandle) <= GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Switching Attack")));
		LastPos = FVector();
		float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer)/* + 0.1f*/;
		GetWorldTimerManager().ClearTimer(SwitchAttackTimer);
		GetWorldTimerManager().SetTimer(SwitchAttackTimer, this, &ARootsOfShadowsCharacter::OnPressAttack2, TimeRemaining);
	}
	//else
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("The cooldown for this attack is not over")));
}

void ARootsOfShadowsCharacter::setEnnemyInRange(int attaque/*1 2 ou 3*/) {
	AEnemyCharacter* enemyTarget = Cast<AEnemyCharacter>(Target);

	int range;

	switch (attaque)
	{
	case 1: range = rangeAttack1; break;
	case 2: range = rangeAttack2; break;
	case 3: range = rangeMagicAttack; break;
	}

	if (enemyTarget) {
		FVector NpcPos = Target->GetActorLocation();
		FVector PlayerPos = this->GetActorLocation();
		float distance = (PlayerPos - NpcPos).Size();

		if (distance <= range) {
			ennemyIsInRangeOfAttack = true;
		}
		else {
			ennemyIsInRangeOfAttack = false;
		}
	}
}

void ARootsOfShadowsCharacter::OnReleaseAttack2()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("OnReleaseAttack2()")));
	bPressed2 = false;
}

void ARootsOfShadowsCharacter::OnPressMagicAttack()
{
	GetWorldTimerManager().ClearTimer(SwitchAttackTimer);

	bPressed3 = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("OnPressMagicAttack()")));

	if (GetWorldTimerManager().GetTimerRemaining(MagicAttackTimerHandle) == -1 && GetWorldTimerManager().GetTimerElapsed(FinishAttackTimer) == -1)
		this->DoMagicAttack();
	else if (GetWorldTimerManager().GetTimerRemaining(MagicAttackTimerHandle) <= GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Switching Attack")));
		LastPos = FVector();
		float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(FinishAttackTimer) /*+ 1.0f*/;
		GetWorldTimerManager().ClearTimer(SwitchAttackTimer);
		GetWorldTimerManager().SetTimer(SwitchAttackTimer, this, &ARootsOfShadowsCharacter::OnPressMagicAttack, TimeRemaining);
	}
	//else
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("The cooldown for this attack is not over")));
}

void ARootsOfShadowsCharacter::OnReleaseMagicAttack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("OnReleaseAttack2()")));
	bPressed3 = false;
}

void ARootsOfShadowsCharacter::UnsetTimerAttack1()
{
	bAttack1TimerExpired = true;
	GetWorldTimerManager().ClearTimer(Attack1TimerHandle);
}

void ARootsOfShadowsCharacter::UnsetTimerAttack2()
{
	bAttack2TimerExpired = true;
	GetWorldTimerManager().ClearTimer(Attack2TimerHandle);
	OnSpecialAttackCooledDown();
}

void ARootsOfShadowsCharacter::UnsetTimerMagicAttack()
{
	bMagicAttackTimerExpired = true;
	GetWorldTimerManager().ClearTimer(MagicAttackTimerHandle);
	OnMagicAttackCooledDown();
}

void ARootsOfShadowsCharacter::setQuestIndex(int index) {
	questIndex = index;
}

void ARootsOfShadowsCharacter::setQuestIndexOneUp() {
	questIndex++;
}

void ARootsOfShadowsCharacter::AcceptQuest() {
	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());	
	TArray<FDBQuest> quests = GameInstance->DatabaseQuests;
	TArray<FDBQuestTask> tasks = GameInstance->DatabaseQuestTasks;

	GameInstance->DatabaseTaskProgress.QuestTaskId = -1;
	FDBQuest current = GameInstance->CurrentQuest;
	
	GameInstance->DatabaseCurrentQuest.CurrentQuest = current.QuestId;

	// Set Task Progress of new quest
	for (int i(0); i < tasks.Num(); i++) {
		if (GameInstance->CurrentQuest.QuestId == tasks[i].QuestId) {
			GameInstance->DatabaseTaskProgress.QuestTaskId = tasks[i].QuestTaskId;
			GameInstance->DatabaseTaskProgress.EnemyId = tasks[i].EnemyId;
			GameInstance->DatabaseTaskProgress.QuantityLeft = tasks[i].QuantityToKill;
		}
	}
	// If next quest has no task, Complete
	if (GameInstance->DatabaseTaskProgress.QuestTaskId == -1)
		GameInstance->DatabaseCurrentQuest.Status = "Complete";
	else
		GameInstance->DatabaseCurrentQuest.Status = "InProgress";
	// Else InProgress

	GameInstance->AcceptQuest(current.QuestId);
}

void ARootsOfShadowsCharacter::CompleteQuest(){
	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());
	GameInstance->DatabaseCurrentQuest.Status = "Complete";
	GameInstance->CompleteQuest(GameInstance->CurrentQuest.QuestId);

	OnQuestComplete();
}

void ARootsOfShadowsCharacter::SetQuestProgress(){

}

void ARootsOfShadowsCharacter::TurnQuest(){
	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());

	GameInstance->DatabaseCurrentQuest.Status = "Turned";
	GameInstance->DatabaseCurrentQuest.CurrentQuest = GameInstance->CurrentQuest.QuestId;

	GainExp(GameInstance->CurrentQuest.ExpReward);

	FDBQuest current = GameInstance->CurrentQuest;
	TArray<FDBQuest> quests = GameInstance->DatabaseQuests;

	for (int i(0); i < quests.Num(); i++) {
		if (quests[i].QuestId == current.QuestId) {
			if (i == quests.Num() - 1)
				GameInstance->CurrentQuest.QuestId = -1;
			else
				GameInstance->CurrentQuest = quests[i + 1];
		}
	}

	GameInstance->TurnQuest(current.QuestId);
	OnQuestComplete();
}

FRotator ARootsOfShadowsCharacter::GetRotationFacingEnnnemy(AEnemyCharacter* enemyTarget) {

	FRotator newRotation = this->GetActorRotation();
	FRotator ennemyRotation = enemyTarget->GetActorRotation();

	newRotation.Yaw = ennemyRotation.Yaw + 180;

	return newRotation;
}

void ARootsOfShadowsCharacter::Die()
{
	if (!IsDead) {
		IsDead = true;
		GetMesh()->PlayAnimation(AnimDeath, false);
		OnDie();
	}	
}

void ARootsOfShadowsCharacter::Respawn() {
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//EnableInput(PlayerController);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());	
	GameInstance->DatabasePlayer.Health = GameInstance->DatabasePlayer.MaxHealth;
	GameInstance->DatabasePlayer.Mana = GameInstance->DatabasePlayer.MaxMana;
	OnManaChanged();
	OnHealthChanged();
	IsDead = false;
}

void ARootsOfShadowsCharacter::ActivatePPLevelUp() {
	LevelUpParticles->ActivateSystem();
}
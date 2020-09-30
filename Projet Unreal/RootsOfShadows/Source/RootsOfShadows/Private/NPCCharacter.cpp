// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "RootsOfShadowsGameState.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
	// Création d'un composant spherique du npc (proximitySphere)
	/*SphereContact = CreateDefaultSubobject<USphereComponent>(TEXT("SphereContactComponent"));
	SphereContact->SetSphereRadius(240.f, false);
	SphereContact->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::BeginOverlap);
	SphereContact->OnComponentEndOverlap.AddDynamic(this, &ANPCCharacter::EndOverlap);
	SphereContact->SetGenerateOverlapEvents(true);
	SphereContact->AttachTo(RootComponent);*/

	overLaping = false;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetQuest();
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	overLaping = true;
}

void ANPCCharacter::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	overLaping = false;
}

void ANPCCharacter::SetQuest() {
	SetQuestUI();
	SetQuestDialogs();
	OnQuestUIChanged();
}

void ANPCCharacter::SetQuestUI() {
	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());
	GameInstance->SetCurrentQuest();
	FString Status = GameInstance->DatabaseCurrentQuest.Status;

	QuestState = "NO";

	// On set le string au bon état selon l'état de la quête et quelle personnage nous sommes
	if (Status == "InProgress") {
		// CurrentQuest = CurrentQuest à finir, NPCStart = ! gris et NPCEnd = ? gris (dans cet ordre)
		if (GameInstance->CurrentQuest.NPCStart == NpcId)
			QuestState = "GE"; // Grey exclamation		
		if (GameInstance->CurrentQuest.NPCEnd == NpcId)
			QuestState = "GI"; // Grey interrogation		
	}
	else if (Status == "Complete") {
		// CurrentQuest = CurrentQuest à rapporter, NPCStart = ! gris et NPCEND = ? jaune
		if (GameInstance->CurrentQuest.NPCStart == NpcId)
			QuestState = "GE";		
		if (GameInstance->CurrentQuest.NPCEnd == NpcId)
			QuestState = "YI"; // Yellow interrogation
	}
	else if (Status == "Turned") {
		// CurrentQuest = La quête disponible, NPCStart = ! jaune et rien pour NPCEnd
		if (GameInstance->CurrentQuest.NPCStart == NpcId && GameInstance->CurrentQuest.QuestId != -1)
			QuestState = "YE"; // Yellow exclamation
	}
}

void ANPCCharacter::SetQuestDialogs() {
	// InProgress = NPCStart takes DialogStatus = "InProgress"
	// Complete = NPCStart takes DialogStatus = "InProgress", NPCEnd takes DialogStatus = "Over"
	// Turned = NPCStart takes DialogStatus = "Begin"

	URootsOfShadowsGameState* GameInstance = Cast<URootsOfShadowsGameState>(GetGameInstance());
	TArray<FDBDialog> Dialogs = GameInstance->DatabaseDialogs;

	FString Status = GameInstance->DatabaseCurrentQuest.Status;	

	DialogTexts.Empty();
	
	// InProgress = NPCStart takes DialogStatus = "InProgress"
	// Complete = NPCStart takes DialogStatus = "InProgress", NPCEnd takes DialogStatus = "Over"
	// Turned = NPCStart takes DialogStatus = "Begin"

	for (int i(0); i < Dialogs.Num(); i++) {
		// On arrête aux dialogues de la quête actuelle
		if (Dialogs[i].QuestId == GameInstance->CurrentQuest.QuestId) {
			// Selon le status de la quête actuelle
			if (Status == "InProgress") {				
				if (Dialogs[i].DialogStatus == "InProgress" && Dialogs[i].NPCStart == NpcId) {
					DialogTexts.Add(Dialogs[i].Text);
					DialogResult = "Talk";
				}					
			}
			else if (Status == "Complete") {
				if (Dialogs[i].DialogStatus == "InProgress" && Dialogs[i].NPCStart == NpcId &&
					Dialogs[i].NPCStart != Dialogs[i].NPCEnd) {
					DialogTexts.Add(Dialogs[i].Text);
					DialogResult = "Talk";
				}					
				if (Dialogs[i].DialogStatus == "Over" && Dialogs[i].NPCEnd == NpcId) {
					DialogTexts.Add(Dialogs[i].Text);
					DialogResult = "Turn";
				}					
			}
			else if (Status == "Turned") {
				if (Dialogs[i].DialogStatus == "Begin" && Dialogs[i].NPCStart == NpcId) {
					DialogTexts.Add(Dialogs[i].Text);
					DialogResult = "Accept";
				}					
			}
		}
	}
}

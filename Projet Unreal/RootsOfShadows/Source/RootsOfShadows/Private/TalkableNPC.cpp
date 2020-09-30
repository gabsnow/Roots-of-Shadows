// Fill out your copyright notice in the Description page of Project Settings.


#include "TalkableNPC.h"
#include "components/spherecomponent.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATalkableNPC::ATalkableNPC()
{
	// Création d'un composant spherique du npc (proximitySphere)
	SphereContact = CreateDefaultSubobject<USphereComponent>(TEXT("SphereContactComponent"));
	SphereContact->SetSphereRadius(240.f, false);
	SphereContact->OnComponentBeginOverlap.AddDynamic(this, &ATalkableNPC::BeginOverlap);
	SphereContact->OnComponentEndOverlap.AddDynamic(this, &ATalkableNPC::EndOverlap);
	SphereContact->SetGenerateOverlapEvents(true);
	RootComponent = SphereContact;

	// Création d'un composant mesh du npc (corps physique)
	NPCMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NpcMesh"));
	NPCMesh->SetOnlyOwnerSee(false);
	NPCMesh->SetupAttachment(SphereContact);
	NPCMesh->bCastDynamicShadow = true;
	NPCMesh->CastShadow = true;

	//Création d'un nom pour le npc


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATalkableNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATalkableNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATalkableNPC::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult) 
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Entered"));
	}
}

void ATalkableNPC::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Leaving"));
	}
}


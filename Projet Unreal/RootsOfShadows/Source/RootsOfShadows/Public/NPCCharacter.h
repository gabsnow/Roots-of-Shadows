// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class ROOTSOFSHADOWS_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	bool bIsSelected;

	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Sphere de contact */
	UPROPERTY(VisibleDefaultsOnly, Category = "TalkableDistance")
	class USphereComponent* SphereContact;

	UPROPERTY(VisibleDefaultsOnly, Category = "WeAreOverlaping")
	bool overLaping;

	// Variable qui détermine quelle UI afficher au dessus de la tête du perso
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestState;

	// Variable qui contient les dialogues à afficher
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> DialogTexts;

	// C'est avec cette variable qu'on va déterminer quoi faire à la fin d'un dialogue:
	// Rien, accepter une quête, ou turn-in une quête
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString DialogResult;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// On set la bonne valeur du QuestState pour pouvoir en jeu afficher le bon QuestUI	
	void SetQuestUI();
	
	// On set les bons dialogues aux NPCs
	void SetQuestDialogs();

	// Appel à SetQuestUI, SetQuestDialogs et à l'événement OnQuestUIChanged
	UFUNCTION(BlueprintCallable)
	void SetQuest();

	// Appelée lorsque le UI change pour prendre en compte les effets dans le jeu
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestUIChanged();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
	int32 NpcId;
};

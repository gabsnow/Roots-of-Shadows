// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <string>
#include "TalkableNPC.generated.h"

UCLASS()
class ROOTSOFSHADOWS_API ATalkableNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATalkableNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Sphere de contact */
	UPROPERTY(VisibleDefaultsOnly, Category = "TalkableDistance")
		class USphereComponent* SphereContact;

	/** Mesh: du NPC  */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* NPCMesh;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

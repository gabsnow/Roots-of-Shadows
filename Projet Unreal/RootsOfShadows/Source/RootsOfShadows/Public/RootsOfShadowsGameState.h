// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include <string>
#include "RootsOfShadowsGameState.generated.h"

// Structures

USTRUCT(BlueprintType)
struct FDBPlayer {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MemberId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PreviousLevelExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextLevelExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Intelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCinematicViewed;
};

USTRUCT(BlueprintType)
struct FDBQuest {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 QuestId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NPCStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NPCEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ExpReward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LevelRequirement;
};

USTRUCT(BlueprintType)
struct FDBDialog {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 QuestId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NPCStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NPCEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Order;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString DialogStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Text;
};

USTRUCT(Blueprintable)
struct FDBEnemy {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EnemyId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ExpGain;
};

USTRUCT(Blueprintable)
struct FDBQuestTask {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 QuestTaskId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 QuestId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EnemyId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 QuantityToKill;
};

USTRUCT(Blueprintable)
struct FDBCurrentQuest {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Status;
};

USTRUCT(Blueprintable)
struct FDBTaskProgress {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestTaskId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuantityLeft;
};

UCLASS()
class ROOTSOFSHADOWS_API URootsOfShadowsGameState : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	FDBPlayer DatabasePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	FDBTaskProgress DatabaseTaskProgress;

	// En fait c'est la derniere quête fait par le joueur
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	FDBCurrentQuest DatabaseCurrentQuest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	TArray<FDBQuest> DatabaseQuests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	TArray<FDBDialog> DatabaseDialogs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	TArray<FDBEnemy> DatabaseEnemies;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	TArray<FDBQuestTask> DatabaseQuestTasks;

	// Réellement CONSIDÉRÉ comme la quête actuelle du joueur, si le Status de DatabaseCurrentQuest == "Turned" alors
	// c'est une quête disponible!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	FDBQuest CurrentQuest;

	FHttpModule* Http;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	bool bLoginWorked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	bool bLoginWorkedProcessed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Database")
	bool bPlayerExists;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	bool bPlayerExistsProcessed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	FString PlayerUsername;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	bool bGetPlayerProcessed;

	bool questsLoaded{ false }, dialogsLoaded{ false }, enemiesLoaded{ false }, tasksLoaded{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	bool bLoadCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	bool bLoadTaskProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
	bool bCurrentQuestLoaded;
	
	URootsOfShadowsGameState();	

	// HTTP Calls

	UFUNCTION(BlueprintCallable)
	void CreatePlayer(FString username, FString playerName);
	void OnCreatePlayerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void GetPlayer(FString username);
	void OnGetPlayerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void Login(FString username, FString password);
	void OnLoginReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void PlayerExists(FString playerName);
	void OnPlayerExistsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void LoadAllQuests();
	void OnLoadAllQuestsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void LoadAllDialogs();
	void OnLoadAllDialogsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void LoadAllEnemies();
	void OnLoadAllEnemiesReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void LoadAllQuestTasks();
	void OnLoadAllQuestTasksReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void LoadPlayerTasks();
	void OnLoadPlayerTasks(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayer();

	UFUNCTION(BlueprintCallable)
	void AcceptQuest(int32 questId);

	UFUNCTION(BlueprintCallable)
	void CompleteQuest(int32 questId);

	UFUNCTION(Blueprintable)
	void SetCurrentQuest();

	UFUNCTION(BlueprintCallable)
	void SetQuestProgress(int32 questId, int32 quantityLeft);

	UFUNCTION(BlueprintCallable)
	void TurnQuest(int32 questId);

	UFUNCTION(BlueprintCallable)
	void LoadCurrentQuest();
	void OnLoadCurrentQuestReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Replace std::string by FString
	FString RemoveSpaces(FString playerName);
};

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

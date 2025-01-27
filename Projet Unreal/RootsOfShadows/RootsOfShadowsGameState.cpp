// Fill out your copyright notice in the Description page of Project Settings.

#include "RootsOfShadowsGameState.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include <string>
#include <algorithm>


URootsOfShadowsGameState::URootsOfShadowsGameState() {
	Http = &FHttpModule::Get();
	DatabasePlayer.MemberId = -1;
	DatabasePlayer.PlayerId = -1;
	DatabaseCurrentQuest.CurrentQuest = -1;
	DatabaseTaskProgress.QuestTaskId = -1;
	CurrentQuest.QuestId = -1;

	LoadAllQuests();
	LoadAllDialogs();
	LoadAllEnemies();
	LoadAllQuestTasks();
}

void URootsOfShadowsGameState::Login(FString username, FString password) {
	bLoginWorkedProcessed = false;
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoginReceived);

	//This is the url on which to process the request
	Request->SetURL("http://farseeds.ca/controllers/unreal.php?request=login&username=" + username + "&password=" + password);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

	PlayerUsername = username;
}

void URootsOfShadowsGameState::OnLoginReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
		bLoginWorked = JsonObject->GetBoolField("valid");

	if (!bLoginWorked)
		PlayerUsername = "";

	bLoginWorkedProcessed = true;
}

void URootsOfShadowsGameState::PlayerExists(FString playerName) {
	bPlayerExistsProcessed = false;

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnPlayerExistsReceived);
	//This is the url on which to process the request
	Request->SetURL("http://farseeds.ca/controllers/unreal.php?request=playerExists&playername=" + RemoveSpaces(playerName));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnPlayerExistsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
		bPlayerExists = JsonObject->GetBoolField("exists");

	bPlayerExistsProcessed = true;
}

void URootsOfShadowsGameState::LoadAllQuests()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoadAllQuestsReceived);

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?request=quests");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnLoadAllQuestsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		auto receivedQuests = JsonObject->GetArrayField("quests");

		for (int i(0); i < receivedQuests.Num(); i++) {
			FDBQuest currentQuest;
			currentQuest.QuestId = receivedQuests[i]->AsObject()->GetIntegerField("QuestId");
			currentQuest.NPCStart = receivedQuests[i]->AsObject()->GetIntegerField("NPCStart");
			currentQuest.NPCEnd = receivedQuests[i]->AsObject()->GetIntegerField("NPCEnd");
			currentQuest.Name = receivedQuests[i]->AsObject()->GetStringField("Name");
			currentQuest.Description = receivedQuests[i]->AsObject()->GetStringField("Description");
			currentQuest.ExpReward = receivedQuests[i]->AsObject()->GetNumberField("ExpReward");
			currentQuest.LevelRequirement = receivedQuests[i]->AsObject()->GetIntegerField("LvlRequirement");

			DatabaseQuests.Add(currentQuest);
		}
	}

	questsLoaded = true;
	bLoadCompleted = questsLoaded && dialogsLoaded && enemiesLoaded && tasksLoaded;
}

void URootsOfShadowsGameState::LoadAllDialogs()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoadAllDialogsReceived);

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?request=dialogs");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnLoadAllDialogsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		auto receivedDialogs = JsonObject->GetArrayField("dialogs");

		for (int i(0); i < receivedDialogs.Num(); i++) {
			FDBDialog currentDialog;

			currentDialog.QuestId = receivedDialogs[i]->AsObject()->GetIntegerField("QuestId");
			currentDialog.NPCStart = receivedDialogs[i]->AsObject()->GetIntegerField("NPCStart");
			currentDialog.NPCEnd = receivedDialogs[i]->AsObject()->GetIntegerField("NPCEnd");
			currentDialog.Order = receivedDialogs[i]->AsObject()->GetIntegerField("Order");
			currentDialog.DialogStatus = receivedDialogs[i]->AsObject()->GetStringField("DialogStatus");
			currentDialog.Text = receivedDialogs[i]->AsObject()->GetStringField("Text");

			DatabaseDialogs.Add(currentDialog);
		}
	}

	dialogsLoaded = true;
	bLoadCompleted = questsLoaded && dialogsLoaded && enemiesLoaded && tasksLoaded;
}

void URootsOfShadowsGameState::LoadAllEnemies()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoadAllEnemiesReceived);

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?request=enemies");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnLoadAllEnemiesReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
		auto receivedEnemies = JsonObject->GetArrayField("enemies");

		for (int i(0); i < receivedEnemies.Num(); i++) {
			FDBEnemy currentEnemy;

			currentEnemy.EnemyId = receivedEnemies[i]->AsObject()->GetIntegerField("EnemyId");
			currentEnemy.Name = receivedEnemies[i]->AsObject()->GetStringField("Name");
			currentEnemy.Level = receivedEnemies[i]->AsObject()->GetIntegerField("Level");
			currentEnemy.Health = receivedEnemies[i]->AsObject()->GetNumberField("Health");
			currentEnemy.Damage = receivedEnemies[i]->AsObject()->GetNumberField("Damage");
			currentEnemy.ExpGain = receivedEnemies[i]->AsObject()->GetNumberField("ExpGain");

			DatabaseEnemies.Add(currentEnemy);
		}
	}

	enemiesLoaded = true;
	bLoadCompleted = questsLoaded && dialogsLoaded && enemiesLoaded && tasksLoaded;
}

void URootsOfShadowsGameState::LoadAllQuestTasks()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoadAllQuestTasksReceived);

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?request=questTasks");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnLoadAllQuestTasksReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
		auto receivedTasks = JsonObject->GetArrayField("questTasks");

		for (int i(0); i < receivedTasks.Num(); i++) {
			FDBQuestTask currentTask;

			currentTask.QuestTaskId = receivedTasks[i]->AsObject()->GetIntegerField("QuestTaskId");
			currentTask.QuestId = receivedTasks[i]->AsObject()->GetIntegerField("QuestId");
			currentTask.EnemyId = receivedTasks[i]->AsObject()->GetIntegerField("EnemyId");
			currentTask.QuantityToKill = receivedTasks[i]->AsObject()->GetIntegerField("QuantityToKill");

			DatabaseQuestTasks.Add(currentTask);
		}
	}

	tasksLoaded = true;
	bLoadCompleted = questsLoaded && dialogsLoaded && enemiesLoaded && tasksLoaded;
}

void URootsOfShadowsGameState::LoadPlayerTasks()
{
	bLoadTaskProgress = false;
	DatabaseTaskProgress.QuestTaskId = -1;

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoadPlayerTasks);

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?request=taskProgress&playerName=" + RemoveSpaces(DatabasePlayer.Name));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnLoadPlayerTasks(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
		auto receivedTasks = JsonObject->GetArrayField("taskProgress");

		if (receivedTasks.Num() > 0) {
			DatabaseTaskProgress.QuestTaskId = receivedTasks[0]->AsObject()->GetIntegerField("QuestTaskId");
			DatabaseTaskProgress.EnemyId = receivedTasks[0]->AsObject()->GetIntegerField("EnemyId");
			DatabaseTaskProgress.QuantityLeft = receivedTasks[0]->AsObject()->GetIntegerField("QuantityLeft");
		}
	}

	bLoadTaskProgress = true;
}

void URootsOfShadowsGameState::CreatePlayer(FString username, FString playerName) {
	FString password = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	//This is the url on which to process the request
	Request->SetURL("http://farseeds.ca/controllers/unreal.php?action=createPlayer&playerName=" + RemoveSpaces(playerName) + "&username=" + username + "&password=" + password);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

	GetPlayer(username);
}

void URootsOfShadowsGameState::OnCreatePlayerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	GetPlayer(PlayerUsername);
}

void URootsOfShadowsGameState::GetPlayer(FString username) {
	bGetPlayerProcessed = false;
	FString password = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnGetPlayerReceived);

	//This is the url on which to process the request
	Request->SetURL("http://farseeds.ca/controllers/unreal.php?request=player&username=" + username);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnGetPlayerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		auto receivedPlayer = JsonObject->GetArrayField("player");

		if (receivedPlayer.Num() > 0) {
			// get and cast the memberId and playerId
			DatabasePlayer.MemberId = receivedPlayer[0]->AsObject()->GetIntegerField("MemberId");
			DatabasePlayer.PlayerId = receivedPlayer[0]->AsObject()->GetIntegerField("PlayerId");

			// get name and username
			DatabasePlayer.Name = receivedPlayer[0]->AsObject()->GetStringField("Name");
			DatabasePlayer.Username = receivedPlayer[0]->AsObject()->GetStringField("username");

			// get and cast all attributes			
			DatabasePlayer.Level = receivedPlayer[0]->AsObject()->GetIntegerField("lvl");
			DatabasePlayer.PreviousLevelExp = receivedPlayer[0]->AsObject()->GetIntegerField("ExpPrevious");
			DatabasePlayer.NextLevelExp = receivedPlayer[0]->AsObject()->GetIntegerField("ExpNext");
			DatabasePlayer.Health = receivedPlayer[0]->AsObject()->GetNumberField("Health");
			DatabasePlayer.MaxHealth = receivedPlayer[0]->AsObject()->GetNumberField("MaxHealth");
			DatabasePlayer.Mana = receivedPlayer[0]->AsObject()->GetNumberField("Mana");
			DatabasePlayer.MaxMana = receivedPlayer[0]->AsObject()->GetNumberField("MaxMana");
			DatabasePlayer.Strength = receivedPlayer[0]->AsObject()->GetNumberField("Strength");
			DatabasePlayer.Money = receivedPlayer[0]->AsObject()->GetNumberField("Money");
			DatabasePlayer.Intelligence = receivedPlayer[0]->AsObject()->GetNumberField("Intelligence");
			DatabasePlayer.Agility = receivedPlayer[0]->AsObject()->GetNumberField("Agility");
			DatabasePlayer.Stealth = receivedPlayer[0]->AsObject()->GetNumberField("Stealth");
			DatabasePlayer.Experience = receivedPlayer[0]->AsObject()->GetNumberField("Experience");
			DatabasePlayer.bCinematicViewed = receivedPlayer[0]->AsObject()->GetBoolField("CinematicViewed");

			// Getting position (trying at least...)
			std::string stringPosition = TCHAR_TO_UTF8(*receivedPlayer[0]->AsObject()->GetStringField("Position"));
			float x = std::stof(stringPosition.substr(0, stringPosition.find(':')));
			stringPosition = stringPosition.substr(stringPosition.find(':') + 1);
			float y = std::stof(stringPosition.substr(0, stringPosition.find(':')));
			stringPosition = stringPosition.substr(stringPosition.find(':') + 1);
			float z = std::stof(stringPosition.substr(0, stringPosition.find(':') - 1));

			DatabasePlayer.Position = FVector(x, y, z);

			LoadCurrentQuest();
		}
	}
	bGetPlayerProcessed = true;
}

void URootsOfShadowsGameState::UpdatePlayer() {
	FString pass = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	FString pos = FString::SanitizeFloat(DatabasePlayer.Position.X) + ":" + FString::SanitizeFloat(DatabasePlayer.Position.Y) + ":" + FString::SanitizeFloat(DatabasePlayer.Position.Z);
	FString viewed = DatabasePlayer.bCinematicViewed ? "true" : "false";

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?action=updatePlayer&pass=" + pass + "&name=" + RemoveSpaces(DatabasePlayer.Name) + "&hp=" + FString::SanitizeFloat(DatabasePlayer.Health) +
		"&maxHp=" + FString::SanitizeFloat(DatabasePlayer.MaxHealth) + "&mp=" + FString::SanitizeFloat(DatabasePlayer.Mana) + "&maxMp=" + FString::SanitizeFloat(DatabasePlayer.MaxMana) +
		"&str=" + FString::SanitizeFloat(DatabasePlayer.Strength) + "&pos=" + pos + "&money=" + FString::SanitizeFloat(DatabasePlayer.Money) + "&int=" + FString::SanitizeFloat(DatabasePlayer.Intelligence) +
		"&agi=" + FString::SanitizeFloat(DatabasePlayer.Agility) + "&stealth=" + FString::SanitizeFloat(DatabasePlayer.Stealth) + "&exp=" + FString::SanitizeFloat(DatabasePlayer.Experience) +
		"&viewed=" + viewed);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::AcceptQuest(int32 questId)
{
	FString pass = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?action=acceptQuest&pass=" + pass + "&playerName=" +
		RemoveSpaces(DatabasePlayer.Name) + "&questId=" + FString::FromInt(questId));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

	//LoadCurrentQuest();
	SetCurrentQuest();
	//LoadPlayerTasks();
}

void URootsOfShadowsGameState::CompleteQuest(int32 questId)
{
	FString pass = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?action=completeQuest&pass=" + pass + "&playerName=" +
		RemoveSpaces(DatabasePlayer.Name) + "&questId=" + FString::FromInt(questId));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::SetCurrentQuest()
{
	CurrentQuest = FDBQuest();
	CurrentQuest.QuestId = -1;

	FString Status = DatabaseCurrentQuest.Status;
	int32 LastQuestDone = DatabaseCurrentQuest.CurrentQuest;

	// On v?rifie quelle est la qu?te actuelle
	if (LastQuestDone == 0)
		CurrentQuest = DatabaseQuests[0];
	else if (Status == "Turned")
		for (int i(0); i < DatabaseQuests.Num(); i++) {
			if (LastQuestDone == DatabaseQuests[i].QuestId && i != DatabaseQuests.Num() - 1) {
				CurrentQuest = DatabaseQuests[i + 1];
			}
		}
	else {
		for (int i(0); i < DatabaseQuests.Num(); i++) {
			if (LastQuestDone == DatabaseQuests[i].QuestId)
				CurrentQuest = DatabaseQuests[i];
		}
	}
}

void URootsOfShadowsGameState::SetQuestProgress(int32 taskId, int32 quantityLeft)
{
	FString pass = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?action=setTaskProgress&pass=" + pass + "&playerName=" +
		RemoveSpaces(DatabasePlayer.Name) + "&taskId=" + FString::FromInt(taskId) + "&qty=" + FString::FromInt(quantityLeft));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::TurnQuest(int32 questId)
{
	FString pass = "AjF53dsa$$!";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?action=turnQuest&pass=" + pass + "&playerName=" +
		RemoveSpaces(DatabasePlayer.Name) + "&questId=" + FString::FromInt(questId));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::LoadCurrentQuest()
{
	bCurrentQuestLoaded = false;

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URootsOfShadowsGameState::OnLoadCurrentQuestReceived);

	//This is the url on which to process the request
	Request->SetURL("https://farseeds.ca/controllers/unreal.php?request=lastQuest&playerName=" + RemoveSpaces(DatabasePlayer.Name));
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void URootsOfShadowsGameState::OnLoadCurrentQuestReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		auto receivedQuest = JsonObject->GetArrayField("lastQuest");
		DatabaseCurrentQuest.CurrentQuest = receivedQuest[0]->AsObject()->GetIntegerField("LastQuest");
		DatabaseCurrentQuest.Status = receivedQuest[0]->AsObject()->GetStringField("Status");

		SetCurrentQuest();
		LoadPlayerTasks();
	}

	bCurrentQuestLoaded = true;
}

FString URootsOfShadowsGameState::RemoveSpaces(FString playerName) {
	std::string cppPlayerName = TCHAR_TO_UTF8(*playerName);
	return FString(ReplaceAll(cppPlayerName, " ", "%20").c_str());
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RootsOfShadows : ModuleRules
{
	public RootsOfShadows(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Http, Json & JsonUtilities = pour les requêtes GET/POST
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","AIModule", "GameplayTasks", "Http", "Json", "JsonUtilities" });
    }
}

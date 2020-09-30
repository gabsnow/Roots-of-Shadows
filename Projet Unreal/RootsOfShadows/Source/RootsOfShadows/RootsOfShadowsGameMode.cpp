// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RootsOfShadowsGameMode.h"
#include "RootsOfShadowsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARootsOfShadowsGameMode::ARootsOfShadowsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RootsOfShadowsCharacter/RootsOfShadowsCharacterBP"));
	
	if (PlayerPawnBPClass.Class != NULL)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}

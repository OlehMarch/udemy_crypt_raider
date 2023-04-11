// Copyright Epic Games, Inc. All Rights Reserved.

#include "crypt_raiderGameMode.h"
#include "crypt_raiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

Acrypt_raiderGameMode::Acrypt_raiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

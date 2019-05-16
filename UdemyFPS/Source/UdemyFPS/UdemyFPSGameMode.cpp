// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UdemyFPSGameMode.h"
#include "UdemyFPSHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUdemyFPSGameMode::AUdemyFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUdemyFPSHUD::StaticClass();
}

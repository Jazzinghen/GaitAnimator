// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GaitAnimator.h"
#include "GaitAnimatorGameMode.h"
#include "GaitAnimatorCharacter.h"

AGaitAnimatorGameMode::AGaitAnimatorGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

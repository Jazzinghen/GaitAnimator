// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GaitAnimator : ModuleRules
{
	public GaitAnimator(TargetInfo Target)
	{
        // Adding sockets to implement basic network functionalities (i.e. activity data streaming)
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Sockets", "Networking", "Json", "JsonUtilities" });
	}
}

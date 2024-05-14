// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class crypt_raider : ModuleRules
{
	public crypt_raider(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}

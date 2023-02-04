// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GodOfRoot : ModuleRules
{
	public GodOfRoot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

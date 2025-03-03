// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrimRandomDistributionSystem : ModuleRules
{
	public CrimRandomDistributionSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"CoreUObject", 
				"GameplayTags",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine", 
				"AIModule",
			}
			);
	}
}

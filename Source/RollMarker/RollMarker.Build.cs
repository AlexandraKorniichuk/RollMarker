// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RollMarker : ModuleRules
{
	public RollMarker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", 
			"InputCore", "EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "Niagara" });
        
        PublicIncludePaths.AddRange(new string[] {
        	"RollMarker/Player",
        	"RollMarker/Components",
        	"RollMarker/AI",
        	"RollMarker/UI",
        });
	}
}

// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

using System.IO;
using UnrealBuildTool;

public class UTFPublisher : ModuleRules
{
	public UTFPublisher(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
        	PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        	PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UTags",
                "UConversions",
                "UROSBridge",
				"Json",
				"JsonUtilities"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}

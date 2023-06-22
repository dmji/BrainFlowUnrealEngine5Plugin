using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class BrainFlowPlugin : ModuleRules
{
	public BrainFlowPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string compiledDir = Path.Combine(ModuleDirectory, "Compiled", "x64_dynamic");
            string libDir = Path.Combine(compiledDir, "lib");

            // lib's
            List<string> aFileLib = new List<string>();
            aFileLib.AddRange(new string[] { "BoardController.lib", "BrainBitLib.lib", "Brainflow.lib", "BrainFlowBluetooth.lib", "DataHandler.lib", "DSPFilters.lib", "GanglionLib.lib", "kissfft-double.lib", "MLModule.lib", "MuseLib.lib", "WaveLib.lib" });
            aFileLib.ForEach(s => PublicAdditionalLibraries.Add(Path.Combine(libDir, s)));
            //foreach (string s in aFileLib)
            //    PublicAdditionalLibraries.Add(Path.Combine(libDir, s));

            // dll's
            string copyDllTo = Path.Combine(PluginDirectory, "Binaries", "Win64");
            List<string> aFileDll = new List<string>();
            aFileDll.AddRange(new string[] { "BoardController.dll", "BrainBitLib.dll", "BrainFlowBluetooth.dll", "DataHandler.dll", "eego-SDK.dll", "GanglionLib.dll", "MLModule.dll", "MuseLib.dll", "neurosdk-x64.dll", "Unicorn.dll" });
            aFileDll.ForEach(s => RuntimeDependencies.Add($"$(TargetOutputDir)/{s}", Path.Combine(libDir, $"{s}")));
            //foreach (string s in aFileDll)
            //    RuntimeDependencies.Add(Path.Combine(copyDllTo, s), Path.Combine(libDir, $"{s}"));

            // includes folder
            PublicIncludePaths.Add(Path.Combine(compiledDir, "inc"));
        }
    }
}

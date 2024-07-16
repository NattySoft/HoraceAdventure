// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class HoraceAdventureEditorTarget : TargetRules
{
	public HoraceAdventureEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "HoraceAdventure" } );
	}
}

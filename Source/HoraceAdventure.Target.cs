// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class HoraceAdventureTarget : TargetRules
{
	public HoraceAdventureTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "HoraceAdventure" } );
	}
}

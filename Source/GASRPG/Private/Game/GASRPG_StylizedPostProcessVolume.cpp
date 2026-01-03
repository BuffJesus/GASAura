// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/GASRPG_StylizedPostProcessVolume.h"

AGASRPG_StylizedPostProcessVolume::AGASRPG_StylizedPostProcessVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Affect entire world
	bUnbound = true;
	
	// Lower priority so gameplay volumes (like enemy highlighting) take precedence
	Priority = 0.5f;
	
	// Apply settings on construction
	ApplyStylizedSettings();
}

void AGASRPG_StylizedPostProcessVolume::BeginPlay()
{
	Super::BeginPlay();
	
	// Reapply in case changes were made in editor
	ApplyStylizedSettings();
}

void AGASRPG_StylizedPostProcessVolume::ApplyStylizedSettings()
{
	// === COLOUR SATURATION & VIBRANCY ===
	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(ColourSaturation, ColourSaturation, ColourSaturation, 1.f);
	
	Settings.bOverride_ColorContrast = true;
	Settings.ColorContrast = FVector4(ColourContrast, ColourContrast, ColourContrast, 1.f);
	
	Settings.bOverride_ColorGamma = true;
	Settings.ColorGamma = FVector4(ColourGamma, ColourGamma, ColourGamma, 1.f);
	
	// Scene tint - neutral by default to preserve particle colors
	Settings.bOverride_SceneColorTint = true;
	Settings.SceneColorTint = SceneTint;
	
	// === SHADOW ENHANCEMENTS ===
	// Make shadows more vibrant and less muddy - critical for cartoon style
	Settings.bOverride_ColorSaturationShadows = true;
	Settings.ColorSaturationShadows = FVector4(ShadowSaturation, ShadowSaturation, ShadowSaturation, 1.f);
	
	Settings.bOverride_ColorContrastShadows = true;
	Settings.ColorContrastShadows = FVector4(ShadowContrast, ShadowContrast, ShadowContrast, 1.f);
	
	Settings.bOverride_ColorCorrectionShadowsMax = true;
	Settings.ColorCorrectionShadowsMax = ShadowsMax;
	
	// === HIGHLIGHT ENHANCEMENTS ===
	Settings.bOverride_ColorSaturationHighlights = true;
	Settings.ColorSaturationHighlights = FVector4(HighlightSaturation, HighlightSaturation, HighlightSaturation, 1.f);
	
	Settings.bOverride_ColorContrastHighlights = true;
	Settings.ColorContrastHighlights = FVector4(HighlightContrast, HighlightContrast, HighlightContrast, 1.f);
	
	// === SHARPENING ===
	// Crisp, clean edges for cartoon style
	Settings.bOverride_Sharpen = true;
	Settings.Sharpen = SharpenAmount;
	
	// === BLOOM ===
	// Controlled bloom for stylized glow without washing out
	Settings.bOverride_BloomIntensity = true;
	Settings.BloomIntensity = BloomIntensity;
	
	Settings.bOverride_BloomThreshold = true;
	Settings.BloomThreshold = BloomThreshold;
	
	// Use Gaussian bloom for cleaner look
	Settings.bOverride_BloomMethod = true;
	Settings.BloomMethod = EBloomMethod::BM_SOG;
	
	// === VIGNETTE ===
	// Subtle vignette to draw focus to center
	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = VignetteIntensity;
	
	// === FILM GRAIN ===
	// Very subtle grain for texture
	Settings.bOverride_FilmGrainIntensity = true;
	Settings.FilmGrainIntensity = FilmGrainIntensity;
	
	// === TONEMAPPER ===
	// Settings for saturated, vibrant cartoon look
	Settings.bOverride_FilmSlope = true;
	Settings.FilmSlope = FilmSlope;
	
	Settings.bOverride_FilmToe = true;
	Settings.FilmToe = FilmToe;
	
	Settings.bOverride_FilmShoulder = true;
	Settings.FilmShoulder = FilmShoulder;
	
	// === AMBIENT OCCLUSION ===
	// Stronger AO for better depth perception in stylized rendering
	Settings.bOverride_AmbientOcclusionIntensity = true;
	Settings.AmbientOcclusionIntensity = AmbientOcclusionIntensity;
	
	Settings.bOverride_AmbientOcclusionRadius = true;
	Settings.AmbientOcclusionRadius = AmbientOcclusionRadius;
	
	Settings.bOverride_AmbientOcclusionQuality = true;
	Settings.AmbientOcclusionQuality = 60.0f;
}

void AGASRPG_StylizedPostProcessVolume::ResetToDefaults()
{
	// More conservative defaults to preserve particle colors
	ColourSaturation = 1.15f;
	ColourContrast = 1.08f;
	ColourGamma = 1.02f;
	SceneTint = FLinearColor(1.0f, 1.0f, 1.0f); // Neutral - no tint
	
	ShadowSaturation = 1.15f;
	ShadowContrast = 1.05f;
	ShadowsMax = 0.12f;
	
	HighlightSaturation = 1.05f;
	HighlightContrast = 1.02f;
	
	SharpenAmount = 0.5f;
	
	BloomIntensity = 0.75f;
	BloomThreshold = 1.2f;
	
	VignetteIntensity = 0.3f;
	FilmGrainIntensity = 0.015f;
	
	FilmSlope = 0.80f;
	FilmToe = 0.52f;
	FilmShoulder = 0.28f;
	
	AmbientOcclusionIntensity = 0.6f;
	AmbientOcclusionRadius = 180.0f;
	
	ApplyStylizedSettings();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GASRPG_StylizedPostProcessVolume.h"

AGASRPG_StylizedPostProcessVolume::AGASRPG_StylizedPostProcessVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	bUnbound = true;
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
	// Colour saturation & vibrancy
	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(ColourSaturation, ColourSaturation, ColourSaturation, 1.f);
	
	Settings.bOverride_ColorContrast = true;
	Settings.ColorContrast = FVector4(ColourContrast, ColourContrast, ColourContrast, 1.f);
	
	Settings.bOverride_ColorGamma = true;
	Settings.ColorGamma = FVector4(ColourGamma, ColourGamma, ColourGamma, 1.f);
	
	// Warm tint for cartoonish feel
	Settings.bOverride_SceneColorTint = true;
	Settings.SceneColorTint = SceneTint;
	
	// Make shadows more vibrant and less muddy
	Settings.bOverride_ColorSaturationShadows = true;
	Settings.ColorSaturationShadows = FVector4(ShadowSaturation, ShadowSaturation, ShadowSaturation, 1.f);
	
	Settings.bOverride_ColorContrastShadows = true;
	Settings.ColorContrastShadows = FVector4(ShadowContrast, ShadowContrast, ShadowContrast, 1.f);
	
	Settings.bOverride_ColorCorrectionShadowsMax = true;
	Settings.ColorCorrectionShadowsMax = ShadowsMax;
	
	// Highlight enhancements
	Settings.bOverride_ColorSaturationHighlights = true;
	Settings.ColorSaturationHighlights = FVector4(HighlightSaturation, HighlightSaturation, HighlightSaturation, 1.f);
	
	Settings.bOverride_ColorContrastHighlights = true;
	Settings.ColorContrastHighlights = FVector4(HighlightContrast, HighlightContrast, HighlightContrast, 1.f);
	
	// Crisp, clean edges for cartoon style
	Settings.bOverride_Sharpen = true;
	Settings.Sharpen = SharpenAmount;
	
	// Controlled bloom, glow without washing out (fingers crossed)
	Settings.bOverride_BloomIntensity = true;
	Settings.BloomIntensity = BloomIntensity;
	
	Settings.bOverride_BloomThreshold = true;
	Settings.BloomThreshold = BloomThreshold;
	
	// Use Gaussian bloom for cleaner look
	Settings.bOverride_BloomMethod = true;
	Settings.BloomMethod = EBloomMethod::BM_SOG;
	
	// Subtle vignette to draw focus to center
	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = VignetteIntensity;
	
	// Very subtle grain for texter
	Settings.bOverride_FilmGrainIntensity = true;
	Settings.FilmGrainIntensity = FilmGrainIntensity;
	
	// Critical settings for saturated, vibrant cartoon look
	Settings.bOverride_FilmSlope = true;
	Settings.FilmSlope = FilmSlope; // Lower = more saturated
	
	Settings.bOverride_FilmToe = true;
	Settings.FilmToe = FilmToe; // Controls shadow rolloff
	
	Settings.bOverride_FilmShoulder = true;
	Settings.FilmShoulder = FilmShoulder; // Controls highlight rolloff
	
	// Stronger AO for better depth perception
	Settings.bOverride_AmbientOcclusionIntensity = true;
	Settings.AmbientOcclusionIntensity = AmbientOcclusionIntensity;
	
	Settings.bOverride_AmbientOcclusionRadius = true;
	Settings.AmbientOcclusionRadius = AmbientOcclusionRadius;
	
	Settings.bOverride_AmbientOcclusionQuality = true;
	Settings.AmbientOcclusionQuality = 60.0f; // Higher quality
}

void AGASRPG_StylizedPostProcessVolume::ResetToDefaults()
{
	ColourSaturation = 1.3f;
	ColourContrast = 1.15f;
	ColourGamma = 1.05f;
	SceneTint = FLinearColor(1.0f, 0.98f, 0.95f);
	
	ShadowSaturation = 1.2f;
	ShadowContrast = 1.1f;
	ShadowsMax = 0.12f;
	
	HighlightSaturation = 1.1f;
	HighlightContrast = 1.05f;
	
	SharpenAmount = 0.6f;
	
	BloomIntensity = 0.9f;
	BloomThreshold = 1.0f;
	
	VignetteIntensity = 0.35f;
	FilmGrainIntensity = 0.025f;
	
	FilmSlope = 0.75f;
	FilmToe = 0.48f;
	FilmShoulder = 0.24f;
	
	AmbientOcclusionIntensity = 0.65f;
	AmbientOcclusionRadius = 180.0f;
	
	ApplyStylizedSettings();
}


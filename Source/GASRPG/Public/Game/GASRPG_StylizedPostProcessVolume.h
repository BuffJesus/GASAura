// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "GASRPG_StylizedPostProcessVolume.generated.h"

/**
 * Stylized post process volume for cartoonish/stylized visuals
 * Place directly in level for best results (will work for all clients)
 */
UCLASS()
class GASRPG_API AGASRPG_StylizedPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

public:
	AGASRPG_StylizedPostProcessVolume();

protected:
	virtual void BeginPlay() override;
	
	// === COLOUR GRADING ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ClampMin = "0.8", ClampMax = "2.0"))
	float ColourSaturation { 1.15f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ClampMin = "0.8", ClampMax = "1.5"))
	float ColourContrast { 1.08f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ToolTip = "Tint the entire scene. Use (1,1,1) for neutral/no tint."))
	FLinearColor SceneTint { FLinearColor(1.f, 1.f, 1.f) };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ClampMin = "0.5", ClampMax = "2.0"))
	float ColourGamma { 1.02f };
	
	// === SHADOW ENHANCEMENT ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Shadow", meta = (ClampMin = "0.8", ClampMax = "1.5"))
	float ShadowSaturation { 1.15f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Shadow", meta = (ClampMin = "0.8", ClampMax = "1.5"))
	float ShadowContrast { 1.05f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Shadow", meta = (ClampMin = "0.0", ClampMax = "0.5"))
	float ShadowsMax { 0.12f };
	
	// === HIGHLIGHTS ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Highlights", meta = (ClampMin = "0.8", ClampMax = "1.3"))
	float HighlightSaturation { 1.05f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Highlights", meta = (ClampMin = "0.8", ClampMax = "1.3"))
	float HighlightContrast { 1.02f };
	
	// === SHARPENING ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Sharpen", meta = (ClampMin = "0.0", ClampMax = "2.0", ToolTip = "Additional sharpening for crisp cartoon edges"))
	float SharpenAmount { 0.5f };
	
	// === BLOOM ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Bloom", meta = (ClampMin = "0.0", ClampMax = "3.0"))
	float BloomIntensity { 0.75f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Bloom", meta = (ClampMin = "-1.0", ClampMax = "8.0"))
	float BloomThreshold { 1.2f };
	
	// === VIGNETTE ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Vignette", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VignetteIntensity { 0.3f };
	
	// === FILM GRAIN ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|FilmGrain", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmGrainIntensity { 0.015f };
	
	// === TONEMAPPER ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Tonemapper", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmSlope { 0.80f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Tonemapper", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmToe { 0.52f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Tonemapper", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmShoulder { 0.28f };
	
	// === AMBIENT OCCLUSION ===
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|AmbientOcclusion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AmbientOcclusionIntensity { 0.6f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|AmbientOcclusion", meta = (ClampMin = "0.0", ClampMax = "500.0"))
	float AmbientOcclusionRadius { 180.0f };
	
	// === FUNCTIONS ===
	
	UFUNCTION(BlueprintCallable, Category = "GASRPG|Stylized")
	void ApplyStylizedSettings();
	
	UFUNCTION(BlueprintCallable, Category = "GASRPG|Stylized")
	void ResetToDefaults();
};
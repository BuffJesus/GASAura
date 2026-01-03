// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "GASRPG_StylizedPostProcessVolume.generated.h"

UCLASS()
class GASRPG_API AGASRPG_StylizedPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

public:
	AGASRPG_StylizedPostProcessVolume();

protected:
	virtual void BeginPlay() override;
	
	// Colour grading
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ClampMin = "0.8", ClampMax = "2.0"))
	float ColourSaturation { 1.3f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ClampMin = "0.8", ClampMax = "1.5"))
	float ColourContrast { 1.15f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour")
	FLinearColor SceneTint { FLinearColor(1.f, 0.98f, 0.95f) };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Colour", meta = (ClampMin = "0.5", ClampMax = "2.0"))
	float ColourGamma { 1.05f };
	
	// Shadow Enhancement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Shadow", meta = (ClampMin = "0.8", ClampMax = "1.5"))
	float ShadowSaturation { 1.2f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Shadow", meta = (ClampMin = "0.8", ClampMax = "1.5"))
	float ShadowContrast { 1.1f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Shadow", meta = (ClampMin = "0.0", ClampMax = "0.5"))
	float ShadowsMax { 0.12f };
	
	// Highlights
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Highlights", meta = (ClampMin = "0.8", ClampMax = "1.3"))
	float HighlightSaturation { 1.1f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Highlights", meta = (ClampMin = "0.8", ClampMax = "1.3"))
	float HighlightContrast { 1.05f };
	
	// Sharpening
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Sharpen", meta = (ClampMin = "0.0", ClampMax = "2.0", ToolTip = "Additional sharpening for crisp cartoon edges"))
	float SharpenAmount { 0.6f };
	
	// Bloom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Highlights", meta = (ClampMin = "0.0", ClampMax = "3.0"))
	float BloomIntensity { 0.9f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Highlights", meta = (ClampMin = "-1.0", ClampMax = "8.0"))
	float BloomThreshold { 1.f };
	
	// Vignette
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Vignette", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VignetteIntensity { 0.35f };
	
	// Film Grain
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|FilmGrain", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmGrainIntensity { 0.025f };
	
	// Tonemapper
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Tonemapper", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmSlope { 0.75f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Tonemapper", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmToe { 0.48f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|Tonemapper", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmShoulder { 0.24f };
	
	// Ambient Occlusion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|AmbientOcclusion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AmbientOcclusionIntensity { 0.65f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Stylized|AmbientOcclusion", meta = (ClampMin = "0.0", ClampMax = "500.0"))
	float AmbientOcclusionRadius { 180.0f };
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "GASRPG|Stylized")
	void ApplyStylizedSettings();
	
	UFUNCTION(BlueprintCallable, Category = "GASRPG|Stylized")
	void ResetToDefaults();
};

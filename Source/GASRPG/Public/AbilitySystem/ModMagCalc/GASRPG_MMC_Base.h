// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AttributeSet.h"
#include "GASRPG_MMC_Base.generated.h"

/**
 * Defines how to apply a coefficient to a value
 */
UENUM(BlueprintType)
enum class EMMCOperationType : uint8
{
	Add      UMETA(DisplayName = "Add (Value + Coefficient)"),
	Multiply UMETA(DisplayName = "Multiply (Value * Coefficient)"),
	Power    UMETA(DisplayName = "Power (Value ^ Coefficient)"),
	None     UMETA(DisplayName = "None (Ignore this term)")
};

/**
 * Defines how to combine the attribute term and level term
 */
UENUM(BlueprintType)
enum class EMMCCombineOperation : uint8
{
	Add      UMETA(DisplayName = "Add (Base + Attr + Level)"),
	Multiply UMETA(DisplayName = "Multiply ((Base + Attr) * Level)"),
	Mixed    UMETA(DisplayName = "Mixed (Base + (Attr * Level))")
};

UCLASS(Blueprintable, BlueprintType)
class GASRPG_API UGASRPG_MMC_Base : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
protected:
	virtual void PostLoad() override;
	
	// Captured attribute used in calculation
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Attribute|Capture")
	FGameplayAttribute AttributeToCapture;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Attribute|Capture", AdvancedDisplay)
	bool bSnapshot { false };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Formula")
	float BaseValue { 0.f };
	
	// How to combine the terms together
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Formula")
	EMMCCombineOperation CombineOperation { EMMCCombineOperation::Add };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Attribute|Term")
	EMMCOperationType AttributeOperation { EMMCOperationType::Multiply };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Attribute|Term")
	float AttributeCoefficient { 1.f };
	
	// How to apply level coefficient
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Level|Term")
	EMMCOperationType LevelOperation { EMMCOperationType::Multiply };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASRPG|Level|Term")
	float LevelCoefficient { 1.f };
	
private:
	void SetupCaptureDefinition();
	float ApplyOperation(float Value, float Coefficient, EMMCOperationType Operation) const;
	FGameplayEffectAttributeCaptureDefinition AttributeDef;
};

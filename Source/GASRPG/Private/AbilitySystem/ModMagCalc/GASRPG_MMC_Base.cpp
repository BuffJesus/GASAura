// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/GASRPG_MMC_Base.h"
#include "Interaction/GASRPG_CombatInterface.h"

float UGASRPG_MMC_Base::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags { Spec.CapturedSourceTags.GetAggregatedTags() };
	const FGameplayTagContainer* TargetTags { Spec.CapturedTargetTags.GetAggregatedTags() };
	
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTags;
	EvalParams.TargetTags = TargetTags;
	
	// Get capture attribute value
	float AttributeValue { 0.f };
	GetCapturedAttributeMagnitude(AttributeDef, Spec, EvalParams, AttributeValue);
	AttributeValue = FMath::Max<float>(AttributeValue, 0.f);
	
	// Get character level
	int32 CharacterLevel { 1 };
	if (IGASRPG_CombatInterface* CombatInterface { Cast<IGASRPG_CombatInterface>(Spec.GetContext().GetSourceObject()) })
	{
		CharacterLevel = CombatInterface->GetCharacterLevel();
	}
	
	// Calculate attribute term
	const float AttributeTerm { ApplyOperation(AttributeValue, AttributeCoefficient, AttributeOperation) };
	
	// Calculate level term
	const float LevelTerm { ApplyOperation(static_cast<float>(CharacterLevel), LevelCoefficient, LevelOperation) };
	
	// Combine base on combine operation
	float Result { 0.f };
	
	switch (CombineOperation)
	{
	case EMMCCombineOperation::Add:
		// Base + AttributeTerm + LevelTerm
		Result = BaseValue + AttributeTerm + LevelTerm;
		break;
		
	case EMMCCombineOperation::Multiply:
		// (Base + AttributeTerm) * LevelTerm
		Result = (BaseValue + AttributeTerm) * LevelTerm;
		break;
		
	case EMMCCombineOperation::Mixed:
		// Base + (AttributeTerm * LevelTerm)
		Result = BaseValue + (AttributeTerm * LevelTerm);
		break;
		
	default:
		Result = BaseValue + AttributeTerm + LevelTerm;
		break;
	}

	return FMath::Max<float>(Result, 0.f);
}

void UGASRPG_MMC_Base::PostLoad()
{
	Super::PostLoad();
	
	// Setup capture def after properties fully loaded from BP
	SetupCaptureDefinition();
}

void UGASRPG_MMC_Base::SetupCaptureDefinition()
{
	if (AttributeToCapture.IsValid())
	{
		AttributeDef.AttributeToCapture = AttributeToCapture;
		AttributeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
		AttributeDef.bSnapshot = bSnapshot;

		RelevantAttributesToCapture.Empty();
		RelevantAttributesToCapture.Add(AttributeDef);
	}
}

float UGASRPG_MMC_Base::ApplyOperation(float Value, float Coefficient, EMMCOperationType Operation) const
{
	switch (Operation)
	{
	case EMMCOperationType::Add:
		return Value + Coefficient;
		
	case EMMCOperationType::Multiply:
		return Value * Coefficient;
		
	case EMMCOperationType::Power:
		return FMath::Pow(Value, Coefficient);
		
	case EMMCOperationType::None:
	default:
		return 0.f;
	}
}

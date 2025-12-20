// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/GASRPG_DefaultAttributesBase.h"

UGASRPG_DefaultAttributesBase::UGASRPG_DefaultAttributesBase()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}

void UGASRPG_DefaultAttributesBase::AddAttributeModifier(const FGameplayAttribute& Attribute, float Value, EGameplayModOp::Type Op)
{
	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = Attribute;
	ModifierInfo.ModifierOp = Op;
	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(Value));
    
	Modifiers.Add(ModifierInfo);
}
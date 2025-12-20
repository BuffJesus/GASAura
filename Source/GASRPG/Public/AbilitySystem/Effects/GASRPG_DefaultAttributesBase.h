// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "AttributeSet.h"
#include "GASRPG_DefaultAttributesBase.generated.h"

UCLASS(Abstract)
class GASRPG_API UGASRPG_DefaultAttributesBase : public UGameplayEffect
{
	GENERATED_BODY()
    
public:
	UGASRPG_DefaultAttributesBase();

protected:
	// Helper function to add attribute modifiers
	void AddAttributeModifier(const FGameplayAttribute& Attribute, float Value, EGameplayModOp::Type Op = EGameplayModOp::Override);
};

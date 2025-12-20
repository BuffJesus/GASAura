// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/GASRPG_DefaultPlayerPrimaryAttributes.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"

UGASRPG_DefaultPlayerPrimaryAttributes::UGASRPG_DefaultPlayerPrimaryAttributes()
{
	AddAttributeModifier(UGASRPG_AttributeSet::GetStrengthAttribute(), 10.f);
	AddAttributeModifier(UGASRPG_AttributeSet::GetIntelligenceAttribute(), 17.f);
	AddAttributeModifier(UGASRPG_AttributeSet::GetResilienceAttribute(), 12.f);
	AddAttributeModifier(UGASRPG_AttributeSet::GetVigorAttribute(), 9.f);
}

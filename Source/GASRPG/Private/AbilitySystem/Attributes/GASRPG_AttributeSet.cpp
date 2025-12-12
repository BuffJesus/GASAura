// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSetMacros.h"

UGASRPG_AttributeSet::UGASRPG_AttributeSet()
{
	InitHealth(10.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);
}

void UGASRPG_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Health);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, MaxHealth);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Mana);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, MaxMana);
}

IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Health);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, MaxHealth);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Mana);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, MaxMana);

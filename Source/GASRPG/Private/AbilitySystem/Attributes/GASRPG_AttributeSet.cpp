// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSetMacros.h"

void UGASRPG_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Health);
}

IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Health);

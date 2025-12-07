// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/GASRPG_PlayerState.h"
#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"

AGASRPG_PlayerState::AGASRPG_PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGASRPG_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet = CreateDefaultSubobject<UGASRPG_AttributeSet>(TEXT("AttributeSet"));
	
	SetNetUpdateFrequency(100.f);
}

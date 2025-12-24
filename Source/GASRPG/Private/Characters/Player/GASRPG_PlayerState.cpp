// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/GASRPG_PlayerState.h"
#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "Net/UnrealNetwork.h"

AGASRPG_PlayerState::AGASRPG_PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGASRPG_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UGASRPG_AttributeSet>(TEXT("AttributeSet"));
	
	SetNetUpdateFrequency(100.f);
}

void AGASRPG_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AGASRPG_PlayerState, Level);
}

void AGASRPG_PlayerState::OnRep_Level(int32 OldLevel)
{
	
}

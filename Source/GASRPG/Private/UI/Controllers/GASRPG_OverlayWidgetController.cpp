// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/GASRPG_OverlayWidgetController.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"

void UGASRPG_OverlayWidgetController::BroadcastInitialValues()
{
	const UGASRPG_AttributeSet* GASRPG_AttributeSet { Cast<UGASRPG_AttributeSet>(AttributeSet) };
	if (GASRPG_AttributeSet == nullptr) return;

	OnHealthChanged.Broadcast(GASRPG_AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(GASRPG_AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(GASRPG_AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(GASRPG_AttributeSet->GetMaxMana());
}

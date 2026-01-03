// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/GASRPG_WidgetController.h"

#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"

void UGASRPG_WidgetController::SetWCParams(const FWCParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UGASRPG_WidgetController::BroadcastInitialValues()
{
	// Override in child classes
}

void UGASRPG_WidgetController::BindCallbacksToDependencies()
{
	// Override in child classes
}

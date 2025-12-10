// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/GASRPG_WidgetController.h"

void UGASRPG_WidgetController::SetWCParams(const FWCParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

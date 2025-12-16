// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/GASRPG_UserWidget.h"

void UGASRPG_UserWidget::SetWidgetController(UObject* NewWidgetController)
{
	WidgetController = NewWidgetController;
	WidgetControllerSet();
}

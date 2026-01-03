// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASRPG_WidgetController.h"
#include "GASRPG_AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGASRPG_AttributeMenuWidgetController : public UGASRPG_WidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};

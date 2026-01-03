// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASRPG_AbilitySystemLibrary.generated.h"

class UGASRPG_OverlayWidgetController;
/**
 * 
 */
UCLASS()
class GASRPG_API UGASRPG_AbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "GASRPG|AbilitySystemLibrary|WidgetController", meta = (WorldContext = "WorldContextObject"))
	static UGASRPG_OverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
};

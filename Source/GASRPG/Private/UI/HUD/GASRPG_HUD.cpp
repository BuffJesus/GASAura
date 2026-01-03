// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GASRPG_HUD.h"
#include "UI/Controllers/GASRPG_AttributeMenuWidgetController.h"
#include "UI/Controllers/GASRPG_OverlayWidgetController.h"
#include "UI/Widgets/GASRPG_UserWidget.h"

namespace
{
	template <typename T>
	T* GetOrCreateWidgetController(TObjectPtr<T>& Controller, UObject* Outer, TSubclassOf<T> ControllerClass, const FWCParams& WCParams)
	{
		if (!Controller)
		{
			Controller = NewObject<T>(Outer, ControllerClass);
			Controller->SetWCParams(WCParams);
			Controller->BindCallbacksToDependencies();
		}
		return Controller;
	}
}

UGASRPG_OverlayWidgetController* AGASRPG_HUD::GetOverlayWidgetController(const FWCParams& WCParams)
{
	return GetOrCreateWidgetController(OverlayWidgetController, this, OverlayWidgetControllerClass, WCParams);
}

UGASRPG_AttributeMenuWidgetController* AGASRPG_HUD::GetAttributeMenuWidgetController(const FWCParams& WCParams)
{
	return GetOrCreateWidgetController(AttributeMenuWidgetController, this, AttributeMenuWidgetControllerClass, WCParams);
}

void AGASRPG_HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set!"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set!"));
	
	UUserWidget* Widget { CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass) };
	OverlayWidget = Cast<UGASRPG_UserWidget>(Widget);
	
	const FWCParams WCParams { PC, PS, ASC, AS };
	UGASRPG_OverlayWidgetController* WidgetController { GetOverlayWidgetController(WCParams) };
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	WidgetController->BindCallbacksToDependencies();
	Widget->AddToViewport();
}
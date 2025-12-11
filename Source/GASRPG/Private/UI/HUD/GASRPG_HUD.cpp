// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GASRPG_HUD.h"
#include "UI/Controllers/GASRPG_OverlayWidgetController.h"
#include "UI/Widgets/GASRPG_UserWidget.h"

UGASRPG_OverlayWidgetController* AGASRPG_HUD::GetOverlayWidgetController(const FWCParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UGASRPG_OverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWCParams(WCParams);
		
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
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
	Widget->AddToViewport();
}



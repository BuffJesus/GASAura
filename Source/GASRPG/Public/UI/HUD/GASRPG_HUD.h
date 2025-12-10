// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/GASRPG_UserWidget.h"
#include "UI/Controllers/GASRPG_OverlayWidgetController.h"
#include "GASRPG_HUD.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API AGASRPG_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UGASRPG_UserWidget> OverlayWidget;
	
	UPROPERTY()
	UGASRPG_OverlayWidgetController* GetOverlayWidgetController(const FWCParams& WCParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGASRPG_UserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UGASRPG_OverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGASRPG_OverlayWidgetController> OverlayWidgetControllerClass;
};

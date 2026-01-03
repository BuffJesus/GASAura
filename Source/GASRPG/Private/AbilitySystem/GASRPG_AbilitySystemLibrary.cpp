// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASRPG_AbilitySystemLibrary.h"
#include "Characters/Player/GASRPG_PlayerState.h"
#include "UI/HUD/GASRPG_HUD.h"

namespace
{
	template <typename T>
	T* GetWidgetControllerFromHUD(const UObject* WorldContextObject, T* (AGASRPG_HUD::*Getter)(const FWCParams&))
	{
		APlayerController* PC { WorldContextObject->GetWorld()->GetFirstPlayerController() };
		if (!PC) return nullptr;
		
		AGASRPG_HUD* HUD { Cast<AGASRPG_HUD>(PC->GetHUD()) };
		if (!HUD) return nullptr;
		
		AGASRPG_PlayerState* PS { PC->GetPlayerState<AGASRPG_PlayerState>() };
		UAbilitySystemComponent* ASC { PS->GetAbilitySystemComponent() };
		UAttributeSet* AS { PS->GetAttributeSet() };
		const FWCParams WCParams { PC, PS, ASC, AS };
		
		return (HUD->*Getter)(WCParams);
	}
}

UGASRPG_OverlayWidgetController* UGASRPG_AbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetControllerFromHUD(WorldContextObject, &AGASRPG_HUD::GetOverlayWidgetController);
}

UGASRPG_AttributeMenuWidgetController* UGASRPG_AbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetControllerFromHUD(WorldContextObject, &AGASRPG_HUD::GetAttributeMenuWidgetController);
}
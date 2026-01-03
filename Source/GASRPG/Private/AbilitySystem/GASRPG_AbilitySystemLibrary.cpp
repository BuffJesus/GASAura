// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASRPG_AbilitySystemLibrary.h"
#include "Characters/Player/GASRPG_PlayerState.h"
#include "UI/HUD/GASRPG_HUD.h"

UGASRPG_OverlayWidgetController* UGASRPG_AbilitySystemLibrary::GetOverlayWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC { WorldContextObject->GetWorld()->GetFirstPlayerController() })
	{
		if (AGASRPG_HUD* HUD { Cast<AGASRPG_HUD>(PC->GetHUD()) })
		{
			AGASRPG_PlayerState* PS { PC->GetPlayerState<AGASRPG_PlayerState>() };
			UAbilitySystemComponent* ASC { PS->GetAbilitySystemComponent() };
			UAttributeSet* AS { PS->GetAttributeSet() };
			const FWCParams WCParams { PC, PS, ASC, AS };
			return HUD->GetOverlayWidgetController(WCParams);
		}
	}
	return nullptr;
}

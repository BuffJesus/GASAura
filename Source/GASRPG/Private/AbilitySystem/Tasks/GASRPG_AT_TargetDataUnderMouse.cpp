// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/GASRPG_AT_TargetDataUnderMouse.h"
#include "Characters/Player/GASRPG_PlayerController.h"

UGASRPG_AT_TargetDataUnderMouse* UGASRPG_AT_TargetDataUnderMouse::CreateTargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UGASRPG_AT_TargetDataUnderMouse* MyObj { NewAbilityTask<UGASRPG_AT_TargetDataUnderMouse>(OwningAbility) };
	return MyObj;
}

void UGASRPG_AT_TargetDataUnderMouse::Activate()
{
	if (const bool bIsLocallyControlled { IsLocallyControlled() })
	{
		SendCursorData();
	}
}

void UGASRPG_AT_TargetDataUnderMouse::SendCursorData()
{
	APlayerController* PC { Ability->GetCurrentActorInfo()->PlayerController.Get() };
	AGASRPG_PlayerController* GASRPGPC { Cast<AGASRPG_PlayerController>(PC) };
	if (GASRPGPC == nullptr) { return; }
	
	FHitResult CursorHit { GASRPGPC->GetCursorHit() };
	OnTargetData.Broadcast(CursorHit.ImpactPoint);
	DrawDebugSphere(GetWorld(), CursorHit.ImpactPoint, 10.0f, 12, FColor::Red, false, 0.1f);
}

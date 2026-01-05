// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/GASRPG_AT_TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
#include "Characters/Player/GASRPG_PlayerController.h"

UGASRPG_AT_TargetDataUnderMouse* UGASRPG_AT_TargetDataUnderMouse::CreateTargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UGASRPG_AT_TargetDataUnderMouse* MyObj { NewAbilityTask<UGASRPG_AT_TargetDataUnderMouse>(OwningAbility) };
	return MyObj;
}

void UGASRPG_AT_TargetDataUnderMouse::Activate()
{
	if (IsLocallyControlled())
	{
		SendCursorData();
	}
	else
	{
		// TODO: We are on server, listen for target data
	}
}

void UGASRPG_AT_TargetDataUnderMouse::SendCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	APlayerController* PC { Ability->GetCurrentActorInfo()->PlayerController.Get() };
	AGASRPG_PlayerController* GASRPGPC { Cast<AGASRPG_PlayerController>(PC) };
	if (GASRPGPC == nullptr) { return; }
	
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data { new FGameplayAbilityTargetData_SingleTargetHit() };
	FHitResult CursorHit { GASRPGPC->GetCursorHit() };
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(), 
		GetActivationPredictionKey(), 
		DataHandle, 
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}


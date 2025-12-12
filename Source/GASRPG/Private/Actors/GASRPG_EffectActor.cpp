// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GASRPG_EffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"

class IAbilitySystemInterface;

AGASRPG_EffectActor::AGASRPG_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void AGASRPG_EffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGASRPG_EffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	UGASRPG_AbilitySystemComponent* TargetASC { (Cast<UGASRPG_AbilitySystemComponent>(
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))) };
	
	if (TargetASC)
	{
		FGameplayEffectContextHandle EffectContextHandle { TargetASC->MakeEffectContext() };
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle { TargetASC->MakeOutgoingSpec(EffectClass, 1.f, EffectContextHandle) };
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}



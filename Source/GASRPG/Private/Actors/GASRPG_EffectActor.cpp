// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GASRPG_EffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

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
	if (!IsValid(TargetActor) || !EffectClass) { return; }
	
	UAbilitySystemComponent* TargetASC { UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) };
	if (!TargetASC) { return; }
	
	FGameplayEffectContextHandle EffectContextHandle { TargetASC->MakeEffectContext() };
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle { TargetASC->MakeOutgoingSpec(EffectClass, 1.f, EffectContextHandle) };
	const FActiveGameplayEffectHandle ActiveEffectHandle { TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()) };
	
	const bool bIsInfinite { EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite };
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// O(1) lookup by actor UID, supports multiple effects per actor
		const uint32 ActorUID { TargetActor->GetUniqueID() };
		ActiveEffectHandles.FindOrAdd(ActorUID).Add(ActiveEffectHandle);
	}
	
	if (bDestroyOnEffectApplication)
	{
		Destroy();
	}
}

void AGASRPG_EffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteEffectClass);
	}
}

void AGASRPG_EffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteEffectClass);
	}
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC { UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) };
		if (!IsValid(TargetASC)) { return; }
		
		const uint32 ActorUID { TargetActor->GetUniqueID() };
		
		// O(1) lookup - no iteration over unrelated entries
		if (TArray<FActiveGameplayEffectHandle>* EffectHandles { ActiveEffectHandles.Find(ActorUID) })
		{
			for (const FActiveGameplayEffectHandle& Handle : *EffectHandles)
			{
				TargetASC->RemoveActiveGameplayEffect(Handle, 1);
			}
			ActiveEffectHandles.Remove(ActorUID);
		}
	}
}
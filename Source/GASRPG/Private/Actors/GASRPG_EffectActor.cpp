// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GASRPG_EffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AGASRPG_EffectActor::AGASRPG_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void AGASRPG_EffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGASRPG_EffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	if (!HasAuthority() || !IsValid(TargetActor) || !EffectClass) { return; }
	
	UAbilitySystemComponent* TargetASC { UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) };
	if (!TargetASC) { return; }
	
	FGameplayEffectContextHandle EffectContextHandle { TargetASC->MakeEffectContext() };
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle { TargetASC->MakeOutgoingSpec(EffectClass, ActorLevel, EffectContextHandle) };
	const FActiveGameplayEffectHandle ActiveEffectHandle { TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()) };
	
	const bool bIsInfinite { EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite };
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
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
	if (!HasAuthority() || !IsValid(TargetActor) || TargetActor == this) { return; }
	
	auto ApplyEffects = [this, TargetActor](EEffectApplicationPolicy Policy, const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
	{
		if (Policy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			for (const TSubclassOf<UGameplayEffect>& EffectClass : EffectClasses)
			{
				ApplyEffectToTarget(TargetActor, EffectClass);
			}
		}
	};
	
	ApplyEffects(InstantEffectApplicationPolicy, InstantEffectClass);
	ApplyEffects(DurationEffectApplicationPolicy, DurationEffectClass);
	ApplyEffects(InfiniteEffectApplicationPolicy, InfiniteEffectClass);
}

void AGASRPG_EffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (!HasAuthority() || !IsValid(TargetActor) || TargetActor == this) { return; }
	
	auto ApplyEffects = [this, TargetActor](EEffectApplicationPolicy Policy, const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
	{
		if (Policy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			for (const TSubclassOf<UGameplayEffect>& EffectClass : EffectClasses)
			{
				ApplyEffectToTarget(TargetActor, EffectClass);
			}
		}
	};
	
	ApplyEffects(InstantEffectApplicationPolicy, InstantEffectClass);
	ApplyEffects(DurationEffectApplicationPolicy, DurationEffectClass);
	ApplyEffects(InfiniteEffectApplicationPolicy, InfiniteEffectClass);
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC { UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) };
		if (!IsValid(TargetASC)) { return; }
		
		const uint32 ActorUID { TargetActor->GetUniqueID() };
		
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"

void UGASRPG_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASRPG_AbilitySystemComponent::ClientEffectApplied);
}

void UGASRPG_AbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& DefaultAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : DefaultAbilities)
	{
		if (AbilityClass)
		{
			const FGameplayAbilitySpec AbilitySpec { FGameplayAbilitySpec(AbilityClass, 1) };
			GiveAbility(AbilitySpec);
		}
	}
}

void UGASRPG_AbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                        const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
 
	EffectAssetTags.Broadcast(TagContainer);
}

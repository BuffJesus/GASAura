// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"

#include "AbilitySystem/Abilities/GASRPG_GA_Base.h"
#include "AbilitySystem/Tags/GASRPG_Tags.h"
#include "Algo/AnyOf.h"

void UGASRPG_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASRPG_AbilitySystemComponent::ClientEffectApplied);
}

void UGASRPG_AbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& DefaultAbilities)
{
	if (!IsOwnerActorAuthoritative() && GetOwnerRole() != ROLE_AutonomousProxy)
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		if (!AbilityClass)
		{
			continue;
		}

		const bool bAbilityAlreadyGranted = Algo::AnyOf(GetActivatableAbilities(), [AbilityClass](const FGameplayAbilitySpec& AbilitySpec)
		{
			return AbilitySpec.Ability && AbilitySpec.Ability->GetClass() == AbilityClass;
		});

		if (bAbilityAlreadyGranted)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec { FGameplayAbilitySpec(AbilityClass, 1) };
		if (const UGASRPG_GA_Base* GASRPGAbility { AbilityClass->GetDefaultObject<UGASRPG_GA_Base>() }) 
		{
			FGameplayTagContainer& DynamicTags { AbilitySpec.GetDynamicSpecSourceTags() };	
			DynamicTags.AddTag(GASRPGAbility->DefaultInputTag);
		}

		GiveAbility(AbilitySpec);
	}
}

void UGASRPG_AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) { return; }
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (const FGameplayTagContainer& DynamicTags { AbilitySpec.GetDynamicSpecSourceTags() }; DynamicTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed( AbilitySpec);
			if (!AbilitySpec.IsActive()) { TryActivateAbility(AbilitySpec.Handle); }
		}
	}
}

void UGASRPG_AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) { return; }
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (const FGameplayTagContainer& DynamicTags { AbilitySpec.GetDynamicSpecSourceTags() }; DynamicTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased( AbilitySpec);
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

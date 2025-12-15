// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/GASRPG_OverlayWidgetController.h"

#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"

void UGASRPG_OverlayWidgetController::BroadcastInitialValues()
{
	const UGASRPG_AttributeSet* GASRPG_AttributeSet { Cast<UGASRPG_AttributeSet>(AttributeSet) };
	if (GASRPG_AttributeSet == nullptr) return;

	OnHealthChanged.Broadcast(GASRPG_AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(GASRPG_AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(GASRPG_AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(GASRPG_AttributeSet->GetMaxMana());
	
}

void UGASRPG_OverlayWidgetController::BindCallbacksToDependencies()
{
	const UGASRPG_AttributeSet* GASRPG_AttributeSet{ Cast<UGASRPG_AttributeSet>(AttributeSet) };

	auto BindAttributeChanged = [this](const FGameplayAttribute& Attribute, auto Callback)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute)
			.AddUObject(this, Callback);
	};

	BindAttributeChanged(GASRPG_AttributeSet->GetHealthAttribute(),    &ThisClass::HealthChanged);
	BindAttributeChanged(GASRPG_AttributeSet->GetMaxHealthAttribute(), &ThisClass::MaxHealthChanged);
	BindAttributeChanged(GASRPG_AttributeSet->GetManaAttribute(),      &ThisClass::ManaChanged);
	BindAttributeChanged(GASRPG_AttributeSet->GetMaxManaAttribute(),   &ThisClass::MaxManaChanged);
	
	Cast<UGASRPG_AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Effect Tag: %s"), *Tag.ToString()));
			}
		}	
	);
}

void UGASRPG_OverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UGASRPG_OverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UGASRPG_OverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UGASRPG_OverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

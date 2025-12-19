// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/GASRPG_OverlayWidgetController.h"
#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "AbilitySystem/Tags/GASRPG_Tags.h"

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

	BindAttributeChangeDelegate(GASRPG_AttributeSet->GetHealthAttribute(),    OnHealthChanged);
	BindAttributeChangeDelegate(GASRPG_AttributeSet->GetMaxHealthAttribute(), OnMaxHealthChanged);
	BindAttributeChangeDelegate(GASRPG_AttributeSet->GetManaAttribute(),      OnManaChanged);
	BindAttributeChangeDelegate(GASRPG_AttributeSet->GetMaxManaAttribute(),   OnMaxManaChanged);
	
	Cast<UGASRPG_AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// Use the parent Message tag
				const FGameplayTag MessageTag { GASRPG::Message::MessageRoot };
				
				// Check if this tag matches "Aura.Message" or any child
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row { GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag) };
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}	
	);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSetMacros.h"
#include "GameFramework/Character.h"

void UGASRPG_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Strength);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Intelligence);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Resilience);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Vigor);
	
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Health);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Mana);
	
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Armor);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, ArmorPenetration);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, BlockChance);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, CriticalHitChance);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, CriticalHitDamage);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, CriticalHitResistance);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, HealthRegen);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, ManaRegen);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, MaxHealth);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, MaxMana);
	REPLICATE_ATTRIBUTE(UGASRPG_AttributeSet, Luck);
}

IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Strength);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Intelligence);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Resilience);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Vigor);

IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Health);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Mana);

IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Armor);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, ArmorPenetration);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, BlockChance);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, CriticalHitChance);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, CriticalHitDamage);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, CriticalHitResistance);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, HealthRegen);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, ManaRegen);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, MaxHealth);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, MaxMana);
IMPLEMENT_ATTRIBUTE_ONREP(UGASRPG_AttributeSet, Luck);

void UGASRPG_AttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	auto ClampToMax = [&NewValue](const float MaxValue, const FString& AttributeName)
	{
		if (MaxValue > 0.f)
		{
			NewValue = FMath::Clamp(NewValue, 0.f, MaxValue);
		}
		else
		{
			// At least prevent negative values even if max is invalid
			NewValue = FMath::Max(NewValue, 0.f);
		}
	};
	
	if (Attribute == GetHealthAttribute())
	{
		ClampToMax(GetMaxHealth(), TEXT("Health"));
	}
	else if (Attribute == GetManaAttribute())
	{
		ClampToMax(GetMaxMana(), TEXT("Mana"));
	}
	
	if (Attribute == GetMaxHealthAttribute() || Attribute == GetMaxManaAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
}

void UGASRPG_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UGASRPG_AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& Props)
{
	// Source = causer of effect, Target = target of effect (owner of this AS)
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && IsValid(Props.SourceASC->GetAvatarActor()))
	{
		Props.SourceAvatarActor = Props.SourceASC->GetAvatarActor();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController && Props.SourceAvatarActor)
		{
			if (const APawn* Pawn { Cast<APawn>(Props.SourceAvatarActor) })
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}





// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GASRPG
{
	namespace Attribute
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute)
		
		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Intelligence)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Strength)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Vigor)
		}
		namespace Resistance
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resistance)
		}
		namespace Secondary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxHealth)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxMana)
		}
		namespace Vital
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Vital)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
		}
	}
	namespace Message
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message)
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthPotion)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthCrystal)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaPotion)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaCrystal)
	}
}


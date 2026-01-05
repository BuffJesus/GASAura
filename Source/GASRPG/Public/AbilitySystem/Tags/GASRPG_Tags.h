// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GASRPG
{
	namespace Attribute
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeRoot)
		
		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrimaryRoot)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Intelligence)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Strength)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Vigor)
		}
		namespace Resistance
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ResistanceRoot)
		}
		namespace Secondary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SecondaryRoot)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ArmorPenetration)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(BlockChance)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(CriticalHitChance)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(CriticalHitDamage)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(CriticalHitResistance)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthRegen)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaRegen)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Luck)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxHealth)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxMana)
		}
		namespace Vital
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(VitalRoot)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
		}
	}
	namespace Event
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventRoot)
		namespace Montage
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MontageRoot)
			namespace Fire
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(FireRoot)
				
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Bolt)
			}
		}
	}
	namespace Input
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputRoot)
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputLMB)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputRMB)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input1)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input2)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input3)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input4)
	}
	namespace Message
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageRoot)
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthPotion)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthCrystal)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaPotion)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaCrystal)
	}
}


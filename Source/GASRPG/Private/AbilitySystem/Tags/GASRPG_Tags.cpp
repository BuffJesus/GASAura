// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tags/GASRPG_Tags.h"

namespace GASRPG
{
	namespace Attribute
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeRoot, "GASRPG.Attribute", "Attribute root")
		
		namespace Primary
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(PrimaryRoot, "GASRPG.Attribute.Primary", "Primary attribute root")
			
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Intelligence, "GASRPG.Attribute.Primary.Intelligence", "Increases magical damage")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience, "GASRPG.Attribute.Primary.Resilience", "Increases armor and armor penetration")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Strength, "GASRPG.Attribute.Primary.Strength", "Increases physical damage")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Vigor, "GASRPG.Attribute.Primary.Vigor", "Increases health")
		}
		namespace Resistance
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(ResistanceRoot, "GASRPG.Attribute.Resistance", "Resistance root")
		}
		namespace Secondary
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(SecondaryRoot, "GASRPG.Attribute.Secondary", "Secondary attribute root")
			
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxHealth, "GASRPG.Attribute.Secondary.MaxHealth", "Maximum amount of health obtainable")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxMana, "GASRPG.Attribute.Secondary.MaxMana", "Maximum amount of mana obtainable")
		}
		namespace Vital
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(VitalRoot, "GASRPG.Attribute.Vital", "Vital attribute root")
			
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health, "GASRPG.Attribute.Vital.Health", "Amount of damage an Actor can take")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mana, "GASRPG.Attribute.Vital.Mana", "Amount of mana an Actor can use")
		}
	}
	namespace Message
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(MessageRoot, "GASRPG.Message", "Message root")
			
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(HealthPotion, "GASRPG.Message.HealthPotion", "Health potion message")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(HealthCrystal, "GASRPG.Message.HealthCrystal", "Health crystal message")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ManaPotion, "GASRPG.Message.ManaPotion", "Mana potion message")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ManaCrystal, "GASRPG.Message.ManaCrystal", "Mana crystal message")
	}
}
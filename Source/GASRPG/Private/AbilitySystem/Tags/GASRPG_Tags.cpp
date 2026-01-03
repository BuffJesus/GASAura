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
			
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Armor, "GASRPG.Attribute.Secondary.Armor", "Reduces damage taken, improves block chance")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(ArmorPenetration, "GASRPG.Attribute.Secondary.ArmorPenetration", "Ignores a percentage of enemy armor, increases critical hit chance")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(BlockChance, "GASRPG.Attribute.Secondary.BlockChance", "Chance to cut incoming damage in half")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(CriticalHitChance, "GASRPG.Attribute.Secondary.CriticalHitChance", "Chance to deal double damage plus critical hit bonus")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(CriticalHitDamage, "GASRPG.Attribute.Secondary.CriticalHitDamage", "Bonus damage added to critical hits")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(CriticalHitResistance, "GASRPG.Attribute.Secondary.CriticalHitResistance", "Reduces critical hit chance of attacking enemies")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HealthRegen, "GASRPG.Attribute.Secondary.HealthRegen", "Amount of health regenerated per second")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(ManaRegen, "GASRPG.Attribute.Secondary.ManaRegen", "Amount of mana regenerated per second")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Luck, "GASRPG.Attribute.Secondary.Luck", "Increases armor penetration, critical hit chance, and block chance")
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
	namespace Input
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputRoot, "GASRPG.Input", "Input root")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputLMB, "GASRPG.Input.LMB", "Left mouse button")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputRMB, "GASRPG.Input.RMB", "Right mouse button")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input1, "GASRPG.Input.1", "First ability key")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input2, "GASRPG.Input.2", "Second ability key")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input3, "GASRPG.Input.3", "Third ability key")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input4, "GASRPG.Input.4", "Fourth ability key")
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
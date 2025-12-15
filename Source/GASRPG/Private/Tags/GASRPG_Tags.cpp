// Fill out your copyright notice in the Description page of Project Settings.


#include "Tags/GASRPG_Tags.h"

namespace GASRPG
{
	namespace Attributes
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes, "GASRPG.Attributes", "Attributes root")
		
		namespace Primary
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GASRPG.Attributes.Primary", "Primary attribute root")
		}
		namespace Secondary
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GASRPG.Attributes.Secondary", "Secondary attribute root")
			
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxHealth, "GASRPG.Attributes.Secondary.MaxHealth", "Maximum amount of health obtainable")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxMana, "GASRPG.Attributes.Secondary.MaxMana", "Maximum amount of mana obtainable")
		}
		namespace Resistance
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resistance, "GASRPG.Attributes.Resistance", "Resistance root")
		}
		namespace Vital
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Vital, "GASRPG.Attributes.Vital", "Vital attribute root")
			
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health, "GASRPG.Attributes.Vital.Health", "Amount of damage an Actor can take")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mana, "GASRPG.Attributes.Vital.Mana", "Amount of mana an Actor can use")
		}
	}
}


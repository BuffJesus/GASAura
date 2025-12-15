// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GASRPG
{
	namespace Attributes
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes)
		
		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
		}
		namespace Secondary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxHealth)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxMana)
		}
		namespace Resistance
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resistance)
		}
		namespace Vital
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Vital)
			
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
		}
	}
}


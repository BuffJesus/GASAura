// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GASRPG_InputConfig.h"

const UInputAction* UGASRPG_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FGASRPG_InputAction& Action: AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOGFMT(LogTemp, Error, "Can't find AbilityInputAction for InputTag [{InputTag}], on InputConfig [{InputConfig}]", InputTag.ToString(), GetNameSafe(this));
	}

	return nullptr;
}

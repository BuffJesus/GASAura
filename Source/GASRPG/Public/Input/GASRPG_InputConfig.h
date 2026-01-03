// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GASRPG_InputConfig.generated.h"

USTRUCT(BlueprintType)
struct FGASRPG_InputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction { nullptr };
	
	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GASRPG.Input"))
	FGameplayTag InputTag { FGameplayTag() };
};

UCLASS()
class GASRPG_API UGASRPG_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGASRPG_InputAction> AbilityInputActions;
};

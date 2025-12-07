// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GASRPG_AttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGASRPG_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Aura|Attributes|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Health);
	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
};

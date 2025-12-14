// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GASRPG_AttributeSet.generated.h"

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties() {}
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC { nullptr };
	
	UPROPERTY()
	AActor* SourceAvatarActor { nullptr };
	
	UPROPERTY()
	AController* SourceController { nullptr };
	
	UPROPERTY()
	ACharacter* SourceCharacter { nullptr };
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC { nullptr };
	
	UPROPERTY()
	AActor* TargetAvatarActor { nullptr };
	
	UPROPERTY()
	AController* TargetController { nullptr };
	
	UPROPERTY()
	ACharacter* TargetCharacter { nullptr };
};

/**
 * 
 */
UCLASS()
class GASRPG_API UGASRPG_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UGASRPG_AttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
#pragma region Vital Attribute Declaration
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "GASRPG|Attributes|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "GASRPG|Attributes|Vital")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Mana);
	
#pragma endregion 
	
#pragma region Secondary Attribute Declaration	
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, MaxMana);
	
#pragma endregion	
	
#pragma region Replication Functions	
	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
#pragma endregion	
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};

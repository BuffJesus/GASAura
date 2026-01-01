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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
#pragma region Primary Attribute Declaration
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "GASRPG|Attributes|Primary")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Strength);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "GASRPG|Attributes|Primary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Intelligence);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "GASRPG|Attributes|Primary")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Resilience);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "GASRPG|Attributes|Primary")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Vigor);
	
#pragma endregion		
	
#pragma region Vital Attribute Declaration
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "GASRPG|Attributes|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "GASRPG|Attributes|Vital")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Mana);
	
#pragma endregion 
	
#pragma region Secondary Attribute Declaration	
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Armor);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, ArmorPenetration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, BlockChance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, CriticalHitChance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, CriticalHitDamage);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, CriticalHitResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, HealthRegen);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, ManaRegen);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Luck, Category = "GASRPG|Attributes|Secondary")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS_BASIC(UGASRPG_AttributeSet, Luck);
	
#pragma endregion	
	
#pragma region Replication Functions	
	
	#pragma region Primary Attribute Rep
	
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience);
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor);
	
	#pragma endregion
	
	#pragma region Vital Attribute Rep
	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	#pragma endregion
	
	#pragma region Secondary Attribute Rep
	
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);
	UFUNCTION() void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);
	UFUNCTION() void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance);
	UFUNCTION() void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);
	UFUNCTION() void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);
	UFUNCTION() void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen);
	UFUNCTION() void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen);
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	UFUNCTION() void OnRep_Luck(const FGameplayAttributeData& OldLuck);
	
	#pragma endregion
	
#pragma endregion	
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};

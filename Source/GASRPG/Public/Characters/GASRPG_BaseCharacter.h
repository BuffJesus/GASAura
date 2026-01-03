// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/GASRPG_CombatInterface.h"
#include "GASRPG_BaseCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class GASRPG_API AGASRPG_BaseCharacter : public ACharacter, public IAbilitySystemInterface, public IGASRPG_CombatInterface
{
	GENERATED_BODY()

public:
	AGASRPG_BaseCharacter();
	
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	};
	
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASRPG|Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "GASRPG|Combat")
	FName WeaponSocket { "WeaponHandSocket" };
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level = 1.f) const;
	void InitializeDefaultAttributes() const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|GAS|Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultPrimaryAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|GAS|Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultSecondaryAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|GAS|Attributes")
	TArray<TSubclassOf<UGameplayEffect>> DefaultVitalAttributes;
	
	void AddCharacterAbilities();
	
private:
	UPROPERTY(EditAnywhere, Category = "GASRPG|GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
};

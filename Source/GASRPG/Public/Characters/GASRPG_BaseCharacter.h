// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASRPG_BaseCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class GASRPG_API AGASRPG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGASRPG_BaseCharacter();
	
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
};

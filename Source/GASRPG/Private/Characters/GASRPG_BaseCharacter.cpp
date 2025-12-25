// Fill out your copyright notice in the Description page of Project Settings.


#include "GASRPG/Public/Characters/GASRPG_BaseCharacter.h"
#include "AbilitySystemComponent.h"



AGASRPG_BaseCharacter::AGASRPG_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), WeaponSocket);
}

void AGASRPG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGASRPG_BaseCharacter::InitAbilityActorInfo()
{

}

void AGASRPG_BaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	checkf(IsValid(EffectClass), TEXT("EffectClass is not set!"));
    
	FGameplayEffectContextHandle ContextHandle { GetAbilitySystemComponent()->MakeEffectContext() };
	ContextHandle.AddSourceObject(this);  // Now GetSourceObject() returns the character
    
	const FGameplayEffectSpecHandle SpecHandle { GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, Level, ContextHandle) };
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AGASRPG_BaseCharacter::InitializeDefaultAttributes() const
{
	for (const auto& EffectClass : DefaultPrimaryAttributes)
		if (IsValid(EffectClass))
			ApplyEffectToSelf(EffectClass);
	for (const auto& EffectClass : DefaultSecondaryAttributes)
		if (IsValid(EffectClass))
			ApplyEffectToSelf(EffectClass);
}

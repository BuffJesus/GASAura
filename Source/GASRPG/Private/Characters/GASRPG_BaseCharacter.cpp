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

void AGASRPG_BaseCharacter::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	checkf(IsValid(DefaultPrimaryAttributes), TEXT("DefaultPrimaryAttributes is not set!"));
	
	const FGameplayEffectContextHandle ContextHandle { GetAbilitySystemComponent()->MakeEffectContext() };
	const FGameplayEffectSpecHandle SpecHandle { GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle) };
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

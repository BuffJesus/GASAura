// Fill out your copyright notice in the Description page of Project Settings.


#include "GASRPG/Public/Characters/GASRPG_BaseCharacter.h"


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

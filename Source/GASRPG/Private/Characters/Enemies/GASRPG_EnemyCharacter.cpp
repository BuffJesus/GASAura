// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/GASRPG_EnemyCharacter.h"
#include "GASRPG/GASRPG.h"

AGASRPG_EnemyCharacter::AGASRPG_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AGASRPG_EnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(true);
		WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AGASRPG_EnemyCharacter::UnhighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(false);
	}
}


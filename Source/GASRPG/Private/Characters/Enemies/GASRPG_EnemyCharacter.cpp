// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/GASRPG_EnemyCharacter.h"

AGASRPG_EnemyCharacter::AGASRPG_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AGASRPG_EnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsHighlighted)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), 100.0f, 12, FColor::Red, false, 0.1f);
	}
}

void AGASRPG_EnemyCharacter::HighlightActor()
{
	bIsHighlighted = true;
}

void AGASRPG_EnemyCharacter::UnhighlightActor()
{
	bIsHighlighted = false;
}


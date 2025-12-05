// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/GASRPG_EnemyCharacter.h"


// Sets default values
AGASRPG_EnemyCharacter::AGASRPG_EnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGASRPG_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGASRPG_EnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGASRPG_EnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


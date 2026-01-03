// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GASRPG_GameModeBase.h"
#include "Game/GASRPG_StylizedPostProcessVolume.h"

void AGASRPG_GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	// Spawn stylized post process volume
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName("StylizedPostProcess");
	
	GetWorld()->SpawnActor<AGASRPG_StylizedPostProcessVolume>(
		AGASRPG_StylizedPostProcessVolume::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParams
	);
}

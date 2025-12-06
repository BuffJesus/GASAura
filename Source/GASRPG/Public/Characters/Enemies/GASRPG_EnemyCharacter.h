// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASRPG_BaseCharacter.h"
#include "Interaction/Interfaces/Enemy/GASRPG_EnemyInterface.h"
#include "GASRPG_EnemyCharacter.generated.h"

UCLASS()
class GASRPG_API AGASRPG_EnemyCharacter : public AGASRPG_BaseCharacter, public IGASRPG_EnemyInterface
{
	GENERATED_BODY()

public:
	
	AGASRPG_EnemyCharacter();
	
	// Interface function overrides
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
};

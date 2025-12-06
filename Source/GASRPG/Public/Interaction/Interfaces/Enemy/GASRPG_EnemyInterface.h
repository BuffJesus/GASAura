// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GASRPG_EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGASRPG_EnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GASRPG_API IGASRPG_EnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighlightActor() = 0;	
	virtual void UnhighlightActor() = 0;
};

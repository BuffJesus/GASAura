// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASRPG_PlayerState.h"
#include "Characters/GASRPG_BaseCharacter.h"
#include "GASRPG_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GASRPG_API AGASRPG_PlayerCharacter : public AGASRPG_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASRPG_PlayerCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASRPG|Movement")
	float RotationRate { 540.f };
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	// Combat interface function overrides
	FORCEINLINE virtual int32 GetCharacterLevel() override
	{
		if (const AGASRPG_PlayerState* PS { GetPlayerState<AGASRPG_PlayerState>() })
		{
			return PS->GetCharacterLevel();
		}
		return 1;
	}

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASRPG|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASRPG|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	virtual void InitAbilityActorInfo() override;
};






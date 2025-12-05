// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASRPG_PlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class GASRPG_API AGASRPG_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGASRPG_PlayerController();
	
protected:
	virtual void BeginPlay() override;	
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "GASRPG|Input")
	TObjectPtr<UInputMappingContext> GASRPGContext;
	
	UPROPERTY(EditAnywhere, Category = "GASRPG|Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
};

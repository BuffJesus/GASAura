// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASRPG_PlayerController.generated.h"

struct FGameplayTag;
class UGASRPG_InputConfig;
class IGASRPG_EnemyInterface;
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "GASRPG|Input")
	TObjectPtr<UInputMappingContext> GASRPGContext;
	
	UPROPERTY(EditAnywhere, Category = "GASRPG|Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
	
	void CursorTrace();
	
	UPROPERTY() FTimerHandle CursorHitTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "GASRPG|Cursor", meta = (ClampMin = "0.05", ClampMax = "0.5"))
	float CursorTraceRate { 0.1f };
	
	UPROPERTY(EditDefaultsOnly, Category = "GASRPG|Input")
	TObjectPtr<UGASRPG_InputConfig> InputConfig;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY() TScriptInterface<IGASRPG_EnemyInterface> LastActor;
	UPROPERTY() TScriptInterface<IGASRPG_EnemyInterface> ThisActor;
};

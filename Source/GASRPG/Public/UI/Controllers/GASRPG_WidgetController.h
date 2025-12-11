// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GASRPG_WidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWCParams
{
	GENERATED_BODY()
	
	FWCParams() {}
	FWCParams(TObjectPtr<APlayerController> PC, TObjectPtr<APlayerState> PS, TObjectPtr<UAbilitySystemComponent> ASC, TObjectPtr<UAttributeSet> AS) 
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<APlayerController> PlayerController { nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<APlayerState> PlayerState { nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent { nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<UAttributeSet> AttributeSet { nullptr };
};
/**
 * 
 */
UCLASS()
class GASRPG_API UGASRPG_WidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWCParams(const FWCParams& WCParams);
	
	virtual void BroadcastInitialValues();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "GASRPG|UI|Controller")
	TObjectPtr<APlayerController> PlayerController { nullptr };
	
	UPROPERTY(BlueprintReadOnly, Category = "GASRPG|UI|Controller")
	TObjectPtr<APlayerState> PlayerState { nullptr };
	
	UPROPERTY(BlueprintReadOnly, Category = "GASRPG|UI|Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent { nullptr };
	
	UPROPERTY(BlueprintReadOnly, Category = "GASRPG|UI|Controller")
	TObjectPtr<UAttributeSet> AttributeSet { nullptr };
	
};

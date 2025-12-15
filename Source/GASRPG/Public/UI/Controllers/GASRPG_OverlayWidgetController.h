// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GASRPG_WidgetController.h"
#include "GASRPG_OverlayWidgetController.generated.h"

class UGASRPG_UserWidget;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "GASRPG.Message"))
	FGameplayTag MessageTag { FGameplayTag() };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MessageText { FText() };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGASRPG_UserWidget> MessageWidget { nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageImage { nullptr };
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GASRPG_API UGASRPG_OverlayWidgetController : public UGASRPG_WidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (RequiredAssetDataTags = "RowStructure=/Script/GASRPG.UIWidgetRow"), Category = "GASRPG|WidgetData")	
	TObjectPtr<UDataTable> MessageWidgetDataTable { nullptr };
	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};

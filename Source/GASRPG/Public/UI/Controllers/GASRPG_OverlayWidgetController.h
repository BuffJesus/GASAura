// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GASRPG_WidgetController.h"
#include "GASRPG_OverlayWidgetController.generated.h"

struct FGameplayAttribute;
class UGASRPG_UserWidget;
struct FOnAttributeChangeData;

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

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
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (RequiredAssetDataTags = "RowStructure=/Script/GASRPG.UIWidgetRow"), Category = "GASRPG|WidgetData")	
	TObjectPtr<UDataTable> MessageWidgetDataTable { nullptr };
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
	template <typename TDelegate>
	void BindAttributeChangeDelegate(const FGameplayAttribute& Attribute, TDelegate& Delegate);
};

template <typename T>
T* UGASRPG_OverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}

template <typename TDelegate>
void UGASRPG_OverlayWidgetController::BindAttributeChangeDelegate(const FGameplayAttribute& Attribute, TDelegate& Delegate)
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute)
		.AddLambda([&Delegate](const FOnAttributeChangeData& Data)
		{
			Delegate.Broadcast(Data.NewValue);
		});
}
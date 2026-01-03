// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASRPG_WidgetController.h"
#include "GASRPG_AttributeMenuWidgetController.generated.h"

struct FAttributeInfo;
class UGASRPG_AttributeInfo;
class UGASRPG_UserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class GASRPG_API UGASRPG_AttributeMenuWidgetController : public UGASRPG_WidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GASRPG|GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
	
	/**
	 * Automatically sets attribute tags on existing row widgets by matching widget names to attribute names
	 * Expected naming convention: Row_<AttributeName> (e.g., Row_Strength, Row_Vigor)
	 * The widget must implement SetAttributeTag(FGameplayTag) function
	 */
	UFUNCTION(BlueprintCallable, Category = "GASRPG|GAS|Attributes")
	void SetAttributeTagsOnExistingRows(UGASRPG_UserWidget* ParentWidget);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGASRPG_AttributeInfo> AttributeInfoClass;
	
private:
	// Helper function to broadcast attribute info w/ current values
	void BroadcastAttributeInfo(const FAttributeInfo& Info) const;
};

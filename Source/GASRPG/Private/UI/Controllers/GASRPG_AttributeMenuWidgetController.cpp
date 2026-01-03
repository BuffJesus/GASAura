// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/GASRPG_AttributeMenuWidgetController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "AbilitySystem/Data/GASRPG_AttributeInfo.h"
#include "Logging/StructuredLog.h"
#include "UI/Widgets/GASRPG_UserWidget.h"

class UGASRPG_AttributeSet;
class UWidget;

void UGASRPG_AttributeMenuWidgetController::BroadcastInitialValues()
{
	if (!AttributeInfoClass)
	{
		UE_LOGFMT(LogTemp, Warning, "AttributeInfo is not set. Unable to broadcast initial values.");
		return;
	}
	
	// Loop through all attributes in DataAsset and broadcast initial values
	for (const FAttributeInfo& Info : AttributeInfoClass->AttributeInfo)
	{
		BroadcastAttributeInfo(Info);
	}
}

void UGASRPG_AttributeMenuWidgetController::BindCallbacksToDependencies()
{
	if (!AttributeInfoClass)
	{
		UE_LOGFMT(LogTemp, Warning, "AttributeInfo is not set. Unable to bind callbacks.");
		return;
	}
	
	// Bind to attribute change delegates for all attributes
	for (const FAttributeInfo& Info : AttributeInfoClass->AttributeInfo)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter)
			.AddLambda([this, Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info);
			});
	}
}

void UGASRPG_AttributeMenuWidgetController::SetAttributeTagsOnExistingRows(UGASRPG_UserWidget* ParentWidget)
{
	if (!ParentWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetAttributeTagsOnExistingRows: ParentWidget is null"));
		return;
	}
	
	if (!AttributeInfoClass)
	{
		UE_LOG(LogTemp, Error, TEXT("AttributeInfo is null in SetAttributeTagsOnExistingRows!"));
		return;
	}
	
	int32 TagsSet { 0 };
	
	// Iterate through all attributes in the DataAsset
	for (const FAttributeInfo& Info : AttributeInfoClass->AttributeInfo)
	{
		// Extract attribute name from tag (e.g., "Strength" from "Aura.Attributes.Primary.Strength")
		FString TagName { Info.AttributeTag.GetTagName().ToString() };
		const int32 LastDotIndex { TagName.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd) };
		FString AttributeName;
		
		if (LastDotIndex != INDEX_NONE)
		{
			AttributeName = TagName.RightChop(LastDotIndex + 1);
		}
		else
		{
			AttributeName = TagName;
		}
		
		// Construct the expected widget name (e.g., "Row_Strength")
		const FString WidgetName { FString::Printf(TEXT("Row_%s"), *AttributeName) };
		
		// Search for widget by name in the parent widget's tree
		UWidget* RowWidget { ParentWidget->GetWidgetFromName(FName(*WidgetName)) };
		
		if (!RowWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not find widget named: %s"), *WidgetName);
			continue;
		}
		
		// Cast to UserWidget to call Blueprint functions
		UGASRPG_UserWidget* RowUserWidget { Cast<UGASRPG_UserWidget>(RowWidget) };
		if (!RowUserWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget %s is not a UserWidget"), *WidgetName);
			continue;
		}
		
		// Call SetAttributeTag function on the widget
		UFunction* SetAttributeTagFunc { RowUserWidget->FindFunction(FName("SetAttributeTag")) };
		if (SetAttributeTagFunc)
		{
			struct FSetAttributeTagParams
			{
				FGameplayTag AttributeTag;
			};
			
			FSetAttributeTagParams Params;
			Params.AttributeTag = Info.AttributeTag;
			RowUserWidget->ProcessEvent(SetAttributeTagFunc, &Params);
			
			TagsSet++;
			UE_LOG(LogTemp, Log, TEXT("Set tag on widget: %s → %s"), *WidgetName, *Info.AttributeTag.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget %s does not have SetAttributeTag function"), *WidgetName);
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Set attribute tags on %d existing row widgets"), TagsSet);
}

void UGASRPG_AttributeMenuWidgetController::BroadcastAttributeInfo(const FAttributeInfo& Info) const
{
	const UGASRPG_AttributeSet* AS { CastChecked<UGASRPG_AttributeSet>(AttributeSet) };
	
	if (!AS)
	{
		UE_LOG(LogTemp, Error, TEXT("AttributeSet is null in BroadcastAttributeInfo!"));
		return;
	}
	
	// Create a copy of Info and update the AttributeValue
	FAttributeInfo NewInfo { Info };
	NewInfo.AttributeValue = Info.AttributeGetter.GetNumericValue(AS);
	
	// Broadcast the updated info to subscribers (attribute menu widget)
	AttributeInfoDelegate.Broadcast(NewInfo);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/GASRPG_AttributeInfo.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "AbilitySystem/Tags/GASRPG_Tags.h"
#include "Logging/StructuredLog.h"

#if WITH_EDITOR
#include "GameplayTagsManager.h"
#endif

FAttributeInfo UGASRPG_AttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAttributeInfo& Info : AttributeInfo)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOGFMT(LogTemp, Warning, "Attribute Tag [{Tag}] not found in GASRPG_AttributeInfo [{AssetName}]",
			("Tag", AttributeTag.ToString()), ("AssetName", GetNameSafe(this)));
	}
	
	return FAttributeInfo();
}

#if WITH_EDITOR
void UGASRPG_AttributeInfo::PopulateDataAsset()
{
	// Clear existing data
	AttributeInfo.Empty();
	
	UGameplayTagsManager& TagManager { UGameplayTagsManager::Get() };
	
	// Get parent tags using native gameplay tags
	const FGameplayTag PrimaryTag { GASRPG::Attribute::Primary::PrimaryRoot };
	const FGameplayTag SecondaryTag { GASRPG::Attribute::Secondary::SecondaryRoot };
	const FGameplayTag ResistanceTag { GASRPG::Attribute::Resistance::ResistanceRoot }; // ADD THIS
	const FGameplayTag VitalTag { GASRPG::Attribute::Vital::VitalRoot };
	
	// Get all gameplay tags
	FGameplayTagContainer AllTags;
	TagManager.RequestAllGameplayTags(AllTags, true);
	
	// Filter to only attribute tags (children of Primary, Secondary, Resistance, or Vital)
	TArray<FGameplayTag> AttributeTags;
	for (const FGameplayTag& Tag : AllTags)
	{
		// Check if tag is a child of Primary, Secondary, Resistance, or Vital (but not the parent tags themselves)
		if ((Tag.MatchesTag(PrimaryTag) && Tag != PrimaryTag) ||
		    (Tag.MatchesTag(SecondaryTag) && Tag != SecondaryTag) ||
		    (Tag.MatchesTag(ResistanceTag) && Tag != ResistanceTag) || // ADD THIS
		    (Tag.MatchesTag(VitalTag) && Tag != VitalTag))
		{
			AttributeTags.Add(Tag);
		}
	}
	
	// Get the AttributeSet class for property lookup
	UClass* AttributeSetClass { UGASRPG_AttributeSet::StaticClass() };
	
	// Process each discovered tag
	for (const FGameplayTag& Tag : AttributeTags)
	{
		// Extract attribute name from tag (last part)
		FString TagName { Tag.GetTagName().ToString() };
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
		
		// Try to find the property in the AttributeSet using reflection
		FProperty* Property { AttributeSetClass->FindPropertyByName(FName(*AttributeName)) };
		if (!Property)
		{
			UE_LOGFMT(LogTemp, Warning, "Could not find property for attribute: {AttributeName}", ("AttributeName", AttributeName));
			continue;
		}
		
		// Verify it's an FGameplayAttributeData property
		FStructProperty* StructProperty { CastField<FStructProperty>(Property) };
		if (!StructProperty || StructProperty->Struct->GetFName() != FName("GameplayAttributeData"))
		{
			UE_LOGFMT(LogTemp, Warning, "Property {PropertyName} is not a GameplayAttributeData", ("PropertyName", AttributeName));
			continue;
		}
		
		// Create the FGameplayAttribute from the property
		FGameplayAttribute GameplayAttribute { Property };
		
		// Format display name (insert spaces before capitals)
		FString FormattedName;
		for (int32 i = 0; i < AttributeName.Len(); ++i)
		{
			if (i > 0 && FChar::IsUpper(AttributeName[i]) && !FChar::IsUpper(AttributeName[i - 1]))
			{
				FormattedName += TEXT(" ");
			}
			FormattedName += AttributeName[i];
		}
		
		// Extract description from DevComment
		FString TagDescription;
		FName FirstTagSource;
		bool bIsTagExplicit { false };
		bool bIsRestrictedTag { false };
		bool bAllowNonRestrictedChildren { false };
		TagManager.GetTagEditorData(Tag.GetTagName(), TagDescription, FirstTagSource, 
			bIsTagExplicit, bIsRestrictedTag, bAllowNonRestrictedChildren);
		
		// Add the attribute info
		AttributeInfo.Add(FAttributeInfo
		{
			Tag,
			FText::FromString(FormattedName),
			FText::FromString(TagDescription.IsEmpty() ? TEXT("No description") : TagDescription),
			0.f,
			GameplayAttribute
		});
		
		UE_LOGFMT(LogTemp, Log, "Added attribute: {AttributeName}", ("AttributeName", FormattedName));
	}
	
	// Sort by tag name for consistency (Primary, Secondary, Resistance, Vital order)
	AttributeInfo.Sort([](const FAttributeInfo& A, const FAttributeInfo& B)
	{
		return A.AttributeTag.GetTagName().ToString() < B.AttributeTag.GetTagName().ToString();
	});
	
	// Mark the asset as modified
	MarkPackageDirty();
	
	UE_LOGFMT(LogTemp, Log, "DataAsset dynamically populated with {Count} attributes", ("Count", AttributeInfo.Num()));
}
#endif
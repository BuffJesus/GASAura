// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASRPG_EffectActor.generated.h"

class UGameplayEffect;

enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class GASRPG_API AGASRPG_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AGASRPG_EffectActor();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = "true"))
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass);
	
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = "true"))
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable, meta = (HideSelfPin = "true"))
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	bool bDestroyOnEffectRemoval { false };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	TSubclassOf<UGameplayEffect> InstantEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy { EEffectApplicationPolicy::DoNotApply };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	TSubclassOf<UGameplayEffect> DurationEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy { EEffectApplicationPolicy::DoNotApply };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	TSubclassOf<UGameplayEffect> InfiniteEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy { EEffectApplicationPolicy::DoNotApply };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy { EEffectRemovalPolicy::RemoveOnEndOverlap };
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASRPG_EffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
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
	bool bDestroyOnEffectApplication { false };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	TArray<TSubclassOf<UGameplayEffect>> InstantEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy { EEffectApplicationPolicy::DoNotApply };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	TArray<TSubclassOf<UGameplayEffect>> DurationEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy { EEffectApplicationPolicy::DoNotApply };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy { EEffectApplicationPolicy::DoNotApply };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy { EEffectRemovalPolicy::RemoveOnEndOverlap };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASRPG|Effects")
	float ActorLevel { 1.f };

private:
	// Use TWeakObjectPtr to prevent holding strong references to actors that might be destroyed
	// This is safe for multiplayer as we're using actual object pointers, not IDs
	TMap<TWeakObjectPtr<AActor>, TArray<FActiveGameplayEffectHandle>> ActiveEffectHandles;
};
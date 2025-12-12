// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASRPG_EffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class GASRPG_API AGASRPG_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AGASRPG_EffectActor();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass);
	
	UPROPERTY(EditAnywhere, Category = "GASRPG|Effects")
	TSubclassOf<UGameplayEffect> InstantEffectClass;
	
};

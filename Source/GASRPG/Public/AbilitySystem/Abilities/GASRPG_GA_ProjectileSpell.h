// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASRPG_GA_Base.h"
#include "GASRPG_GA_ProjectileSpell.generated.h"

class AGASRPG_Projectile;
/**
 * 
 */
UCLASS()
class GASRPG_API UGASRPG_GA_ProjectileSpell : public UGASRPG_GA_Base
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "GASRPG|Abilities")
	void SpawnProjectile();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGASRPG_Projectile> ProjectileClass;
};

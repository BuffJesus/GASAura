// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GASRPG_GA_ProjectileSpell.h"
#include "Actors/GASRPG_Projectile.h"
#include "Interaction/GASRPG_CombatInterface.h"

void UGASRPG_GA_ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	const bool bIsServer { HasAuthority(&ActivationInfo) };
	if (!bIsServer) { return; }
	
	IGASRPG_CombatInterface* CombatInterface { Cast<IGASRPG_CombatInterface>(GetAvatarActorFromActorInfo()) };
	if (CombatInterface)
	{
		const FVector SocketLocation { CombatInterface->GetCombatSocketLocation() };
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		AGASRPG_Projectile* Projectile { GetWorld()->SpawnActorDeferred<AGASRPG_Projectile>(
			ProjectileClass, 
			SpawnTransform, 
			GetOwningActorFromActorInfo(), 
			Cast<APawn>(GetAvatarActorFromActorInfo()), 
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn) };
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

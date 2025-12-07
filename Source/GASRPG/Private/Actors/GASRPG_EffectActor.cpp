// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GASRPG_EffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Attributes/GASRPG_AttributeSet.h"
#include "Components/SphereComponent.h"

AGASRPG_EffectActor::AGASRPG_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->SetSphereRadius(100.0f);
	CollisionSphere->SetCollisionProfileName("OverlapAll");
}

void AGASRPG_EffectActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface { Cast<IAbilitySystemInterface>(OtherActor) })
	{
		const UGASRPG_AttributeSet* GASRPGAttributeSet = Cast<UGASRPG_AttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UGASRPG_AttributeSet::StaticClass())); 
		UGASRPG_AttributeSet* MutableGASRPGAttributeSet = const_cast<UGASRPG_AttributeSet*>(GASRPGAttributeSet);
		MutableGASRPGAttributeSet->SetHealth(MutableGASRPGAttributeSet->GetHealth() + 25.0f);
	}
}

void AGASRPG_EffectActor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AGASRPG_EffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGASRPG_EffectActor::OnOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AGASRPG_EffectActor::EndOverlap);
}

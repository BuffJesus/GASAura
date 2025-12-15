// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/GASRPG_PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Player/GASRPG_PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/HUD/GASRPG_HUD.h"

AGASRPG_PlayerCharacter::AGASRPG_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, RotationRate, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void AGASRPG_PlayerCharacter::InitAbilityActorInfo()
{
	if (AGASRPG_PlayerState* PS { GetPlayerState<AGASRPG_PlayerState>() })
	{
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		Cast<UGASRPG_AbilitySystemComponent>(PS->GetAbilitySystemComponent())->AbilityActorInfoSet();
		AttributeSet = PS->GetAttributeSet();

		// Init overlay, all params should be valid
		if (APlayerController* PC { Cast<APlayerController>(GetController()) })
		{
			if (AGASRPG_HUD* HUD { Cast<AGASRPG_HUD>(PC->GetHUD()) })
			{
				HUD->InitOverlay(PC, PS, AbilitySystemComponent, AttributeSet);
			}
		}
	}
}

void AGASRPG_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info server
	InitAbilityActorInfo();
}

void AGASRPG_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
    
	// Init ability actor info client
	InitAbilityActorInfo();
}



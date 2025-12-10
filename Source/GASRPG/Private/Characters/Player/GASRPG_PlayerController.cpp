// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/GASRPG_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/Player/GASRPG_PlayerCharacter.h"
#include "Interaction/Interfaces/Enemy/GASRPG_EnemyInterface.h"

AGASRPG_PlayerController::AGASRPG_PlayerController()
{
	bReplicates = true;
}

void AGASRPG_PlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) { return; }
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	if (ThisActor != LastActor)
	{
		if (LastActor != nullptr)
		{
			LastActor->UnhighlightActor();
		}
 
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
}

void AGASRPG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GASRPGContext);
	
	GetWorld()->GetTimerManager().SetTimer(CursorHitTimerHandle, this, &AGASRPG_PlayerController::CursorTrace, CursorTraceRate, true);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem { ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) })
	{
		Subsystem->AddMappingContext(GASRPGContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AGASRPG_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(CursorHitTimerHandle);
}

void AGASRPG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent { CastChecked<UEnhancedInputComponent>(InputComponent) };
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGASRPG_PlayerController::Move);
}

void AGASRPG_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector { InputActionValue.Get<FVector2D>() };
	
	if (APawn* ControlledPawn { GetPawn<APawn>() })
	{
		ControlledPawn->AddMovementInput(FVector::ForwardVector, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(FVector::RightVector, InputAxisVector.X);
	}
}



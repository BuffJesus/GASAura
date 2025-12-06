// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/GASRPG_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/Player/GASRPG_PlayerCharacter.h"

AGASRPG_PlayerController::AGASRPG_PlayerController()
{
	bReplicates = true;
}

void AGASRPG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GASRPGContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem { ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) };
	check(Subsystem);
	Subsystem->AddMappingContext(GASRPGContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
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

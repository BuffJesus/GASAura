// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/GASRPG_PlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/GASRPG_AbilitySystemComponent.h"
#include "AbilitySystem/Tags/GASRPG_Tags.h"
#include "Components/SplineComponent.h"
#include "Input/GASRPG_InputComponent.h"
#include "Interaction/Interfaces/Enemy/GASRPG_EnemyInterface.h"
#include "GASRPG/GASRPG.h"

AGASRPG_PlayerController::AGASRPG_PlayerController()
{
	bReplicates = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void AGASRPG_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
	AutoRun();
}

void AGASRPG_PlayerController::AutoRun()
{
	if (!bAutoRunning) { return; }
	
	if (APawn* ControlledPawn { GetPawn() })
	{
		const FVector LocationOnSpline { SplineComponent->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World) };
		const FVector Direction { SplineComponent->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World) };
		ControlledPawn->AddMovementInput(Direction);
		
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
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

void AGASRPG_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(GASRPG::Input::InputLMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AGASRPG_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(GASRPG::Input::InputLMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn { GetPawn<APawn>() };
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			// Use ECC_Navigation channel to trace through obstacles and hit navigable surfaces
			FHitResult NavChannelCursorHitResult;
			GetHitResultUnderCursor(ECC_Navigation, false, NavChannelCursorHitResult);
			
			if (NavChannelCursorHitResult.bBlockingHit)
			{
				// Project the impact point to the NavMesh with a larger query extent
				FVector NavLocation;
				if (FindNavigableDestination(NavChannelCursorHitResult.ImpactPoint, NavLocation))
				{
					if (UNavigationPath* NavPath { UNavigationSystemV1::FindPathToLocationSynchronously(
						this, ControlledPawn->GetActorLocation(), NavLocation) })
					{
						if (NavPath->PathPoints.Num() > 0)
						{
							SplineComponent->ClearSplinePoints();
							for (const FVector& PointLoc : NavPath->PathPoints)
							{
								SplineComponent->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
								DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
							}
							CachedDestination = NavPath->PathPoints.Last();
							bAutoRunning = true;
						}
					}
				}
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AGASRPG_PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(GASRPG::Input::InputLMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		// Use ECC_Navigation channel for click-to-move - traces through obstacles
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Navigation, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
		
		if (APawn* ControlledPawn { GetPawn() })
		{
			const FVector WorldDirection { (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal() };
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UGASRPG_AbilitySystemComponent* AGASRPG_PlayerController::GetASC() 
{
	if (GASRPGASC == nullptr)
	{
		GASRPGASC = Cast<UGASRPG_AbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return GASRPGASC;
}

bool AGASRPG_PlayerController::FindNavigableDestination(const FVector& WorldLocation, FVector& OutNavLocation) const
{
	if (!NavSystem) { return false; }
	
	FNavLocation NavLocation;
	const FNavAgentProperties& NavAgentProps { GetNavAgentPropertiesRef() };
	
	if (NavSystem->ProjectPointToNavigation(WorldLocation, NavLocation, NavQueryExtent, &NavAgentProps))
	{
		OutNavLocation = NavLocation.Location;
		return true;
	}
	
	return false;
}

void AGASRPG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GASRPGContext);
	
	// Cache the navigation system for pathfinding
	NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem { 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) })
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

void AGASRPG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UGASRPG_InputComponent* GASRPGInputComponent { CastChecked<UGASRPG_InputComponent>(InputComponent) };
	GASRPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGASRPG_PlayerController::Move);
	
	GASRPGInputComponent->BindAbilityActions(InputConfig, this, 
		&ThisClass::AbilityInputTagPressed, 
		&ThisClass::AbilityInputTagReleased, 
		&ThisClass::AbilityInputTagHeld);
}

void AGASRPG_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector { InputActionValue.Get<FVector2D>() };
	const FRotator Rotation { GetControlRotation() };
	const FRotator YawRotation { 0.f, Rotation.Yaw, 0.f };
	
	const FVector ForwardDirection { FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) };
	const FVector RightDirection { FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) };
	
	if (APawn* ControlledPawn { GetPawn<APawn>() })
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
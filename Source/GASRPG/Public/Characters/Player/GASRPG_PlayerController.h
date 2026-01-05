// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GASRPG_PlayerController.generated.h"

struct FGameplayTag;
class UGASRPG_InputConfig;
class IGASRPG_EnemyInterface;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UGASRPG_AbilitySystemComponent;
class USplineComponent;
class UNavigationSystemV1;
/**
 * 
 */
UCLASS()
class GASRPG_API AGASRPG_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGASRPG_PlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	FORCEINLINE FHitResult GetCursorHit() const { return CursorHit; }

protected:
	virtual void BeginPlay() override;	
	virtual void SetupInputComponent() override;
	FHitResult CursorHit;
	
private:
	UPROPERTY(EditAnywhere, Category = "GASRPG|Input")
	TObjectPtr<UInputMappingContext> GASRPGContext;
	
	UPROPERTY(EditAnywhere, Category = "GASRPG|Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
	
	void CursorTrace();
	void AutoRun();
	
	UPROPERTY(EditDefaultsOnly, Category = "GASRPG|Input")
	TObjectPtr<UGASRPG_InputConfig> InputConfig;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY() TScriptInterface<IGASRPG_EnemyInterface> LastActor;
	UPROPERTY() TScriptInterface<IGASRPG_EnemyInterface> ThisActor;
	
	UPROPERTY()
	TObjectPtr<UGASRPG_AbilitySystemComponent> GASRPGASC;
	
	UGASRPG_AbilitySystemComponent* GetASC();
	
	FVector CachedDestination { FVector::ZeroVector };
	float FollowTime { 0.f };
	float ShortPressThreshold { 0.5f };
	bool bAutoRunning { false };
	bool bTargeting { false };
	
	UPROPERTY(EditDefaultsOnly, Category = "GASRPG|Navigation")
	float AutoRunAcceptanceRadius { 50.f };
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent { nullptr };
	
	// Navigation system reference for pathfinding
	UPROPERTY()
	TObjectPtr<UNavigationSystemV1> NavSystem { nullptr };
	
	// Query extent for ProjectPointToNavigation - larger than default for better NavMesh reach
	UPROPERTY(EditDefaultsOnly, Category = "GASRPG|Navigation")
	FVector NavQueryExtent { 400.f, 400.f, 250.f };
	
	// Helper to find a valid navigation destination from a world location
	bool FindNavigableDestination(const FVector& WorldLocation, FVector& OutNavLocation) const;
};
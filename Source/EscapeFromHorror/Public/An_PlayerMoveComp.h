// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "An_PlayerBaseComp.h"
#include "An_PlayerMoveComp.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMHORROR_API UAn_PlayerMoveComp : public UAn_PlayerBaseComp
{
	GENERATED_BODY()
public:

	UAn_PlayerMoveComp();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PlayerInputBinding(class UInputComponent* PlayerInputComponent) override;

public:

	FVector dir; //플레이어 이동 방향 속성
	float CruchSpeed = 100;
	float walkSpeed = 150;
	float runSpeed = 250;

	bool isCrouch;
	bool isClimb;

	void OnAxisMoveForward(float value);
	void OnAxisMoveRight(float value);

	void OnActionJump();

	void OnActionRunPressed();
	void OnActionRunReleased();

	void OnActionCruchPressed();
	void OnActionCruchReleased();

	void OnActionClimbPressed();
	void OnActionClimbReleased();
};



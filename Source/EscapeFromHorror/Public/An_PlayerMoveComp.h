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
	FVector climbUp; // 클라임시 이동방향 속성

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cruchSpeed = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float walkSpeed = 150;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float runSpeed = 250;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float climbSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* climUpAnimMontage;


	bool isCrouch;
	bool isClimb;
	bool isClimbUp;
	float myYaw;

	void OnAxisMoveForward(float value);
	void OnAxisMoveRight(float value);

	void OnActionJump();

	void OnActionRunPressed();
	void OnActionRunReleased();

	void OnActionCruchPressed();
	void OnActionCruchReleased();

	void OnActionClimbPressed();
	void OnActionClimbReleased();

	void InClimb();
	void OutClimb();

	void PlayClimbUpAnim();
};



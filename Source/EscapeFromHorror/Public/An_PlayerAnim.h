// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "An_PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMHORROR_API UAn_PlayerAnim : public UAnimInstance
{
GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speedForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speedRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isCrouch;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "An_PlayerAnim.h"
#include "An_PlayerAnimSound.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMHORROR_API UAn_PlayerAnimSound : public UAn_PlayerAnim
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* walkSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* runSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* crouchSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* jumpSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* randSound;

	UFUNCTION(BlueprintCallable)
		void WalkSoundPlay();
	UFUNCTION(BlueprintCallable)
		void RunSoundPlay();
	UFUNCTION(BlueprintCallable)
		void CrouchSoundPlay();
	UFUNCTION(BlueprintCallable)
		void JumpSoundPlay();
	UFUNCTION(BlueprintCallable)
		void RandSoundPlay();
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "An_PlayerBaseComp.h"
#include "An_PlayerCameraComp.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EcameraState : uint8
{
	stage1,
	stage2,
	stage3
};

UCLASS()
class ESCAPEFROMHORROR_API UAn_PlayerCameraComp : public UAn_PlayerBaseComp
{
	GENERATED_BODY()

public:
	UAn_PlayerCameraComp();

protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> cameraPositions_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> cameraPositions_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> cameraPositions_3;

	UPROPERTY(EditAnywhere)
	TArray<FVector> currntCameraState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed = 0.05;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float turnSpeed = 0.05;

	EcameraState cameraState;

	//UPROPERTY(EditAnywhere)
	//class USpringArmComponent* springArm;
	
};

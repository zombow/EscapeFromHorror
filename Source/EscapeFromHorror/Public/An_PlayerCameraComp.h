// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "An_PlayerBaseComp.h"
#include "An_PlayerCameraComp.generated.h"

/**
 * 
 */
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

	//UPROPERTY(EditAnywhere)
	//class USpringArmComponent* springArm;

};

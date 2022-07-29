// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "An_Player.generated.h"

UCLASS()
class ESCAPEFROMHORROR_API AAn_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAn_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;

	FVector dir; //플레이어 이동 방향 속성

	void OnAxisMoveForward(float value);
	void OnAxisMoveRight(float value);
	void OnActionJump();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "An_Player.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnPlayerInputBindingDelegate, class UInputComponent*); // (델리게이트 이름 , 넘겨받을 타입)

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

	OnPlayerInputBindingDelegate onPlayerInputBindingDelegate;

	UPROPERTY(EditAnywhere)
	class UAn_PlayerBaseComp* cameraComp;

	UPROPERTY(EditAnywhere)
	class UAn_PlayerBaseComp* moveComp;

};

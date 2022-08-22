// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "An_CameraController.generated.h"

UCLASS()
class ESCAPEFROMHORROR_API AAn_CameraController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAn_CameraController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	class AAn_Player* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACameraActor* playerCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int xValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int yValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int zValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float xPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float yPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float zPower;

	void CameraMove();

	void CameraLook();
};

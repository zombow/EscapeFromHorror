// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "An_Player.h"
#include "An_CameraActor.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMHORROR_API AAn_CameraActor : public ACameraActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	class AActor* me;
	class AAn_Player* player;

};

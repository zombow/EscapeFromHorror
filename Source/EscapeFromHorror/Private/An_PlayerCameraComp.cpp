// Fill out your copyright notice in the Description page of Project Settings.


#include "An_PlayerCameraComp.h"

#include "Camera/CameraAnim.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UAn_PlayerCameraComp::UAn_PlayerCameraComp()
{

}

void UAn_PlayerCameraComp::BeginPlay()
{
	Super::BeginPlay();
	springArmComp = me->springArmComp;
	cameraComp = me->cameraComp;
}

void UAn_PlayerCameraComp::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

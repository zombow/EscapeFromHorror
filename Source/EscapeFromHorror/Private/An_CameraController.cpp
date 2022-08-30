// Fill out your copyright notice in the Description page of Project Settings.


#include "An_CameraController.h"

#include "An_Player.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "An_PlayerCameraComp.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAn_CameraController::AAn_CameraController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	boxComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAn_CameraController::BeginPlay()
{
	Super::BeginPlay();
	
	player =Cast<AAn_Player>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	playerCamera = Cast<UAn_PlayerCameraComp>(player->cameraComp);
	
}

// Called every frame
void AAn_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAn_CameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void AAn_CameraController::OnNextMap()
{
	if (stageNumber == 1) {
		playerCamera->cameraState = EcameraState::stage1;
	}
	else if (stageNumber == 2) {
		playerCamera->cameraState = EcameraState::stage2;
	}
	else if (stageNumber == 3) {
		playerCamera->cameraState = EcameraState::stage3;
	}
	else
		playerCamera->cameraState = EcameraState::stage4;

}

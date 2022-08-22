// Fill out your copyright notice in the Description page of Project Settings.


#include "An_CameraController.h"

#include "An_Player.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAn_CameraController::AAn_CameraController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAn_CameraController::BeginPlay()
{
	Super::BeginPlay();
	
	player =Cast<AAn_Player>(GetWorld()->GetFirstPlayerController()->GetCharacter());

}

// Called every frame
void AAn_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *player->GetName());

	CameraMove();
	CameraLook();
}

// Called to bind functionality to input
void AAn_CameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAn_CameraController::CameraMove()
{
	playerCam->SetActorLocation(FVector((player->GetActorLocation().X * xPower) + xValue,
		(player->GetActorLocation().Y * yPower) + yValue, 
		(player->GetActorLocation().Z * zPower) + zValue));
}

void AAn_CameraController::CameraLook()
{
	playerCam->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(playerCam->GetActorLocation(), player->GetActorLocation()));
}

